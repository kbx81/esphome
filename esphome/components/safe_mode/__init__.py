from esphome.cpp_generator import RawExpression
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
    CONF_NUM_ATTEMPTS,
    CONF_REBOOT_TIMEOUT,
    CONF_SAFE_MODE,
    KEY_PAST_SAFE_MODE,
)
from esphome.core import CORE, coroutine_with_priority


CODEOWNERS = ["@paulmonigatti", "@jsuanet", "@kbx81"]

safe_mode_ns = cg.esphome_ns.namespace("safe_mode")
SafeModeComponent = safe_mode_ns.class_("SafeModeComponent", cg.Component)


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SafeModeComponent),
        cv.Optional(CONF_NUM_ATTEMPTS, default="10"): cv.positive_not_null_int,
        cv.Optional(
            CONF_REBOOT_TIMEOUT, default="5min"
        ): cv.positive_time_period_milliseconds,
    }
).extend(cv.COMPONENT_SCHEMA)


@coroutine_with_priority(50.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    condition = var.should_enter_safe_mode(
        config[CONF_NUM_ATTEMPTS], config[CONF_REBOOT_TIMEOUT]
    )
    cg.add(RawExpression(f"if ({condition}) return"))
    CORE.data[CONF_SAFE_MODE] = {}
    CORE.data[CONF_SAFE_MODE][KEY_PAST_SAFE_MODE] = True
