#pragma once
#include "ota_backend.h"

namespace esphome {
namespace ota {

std::unique_ptr<ota::OTABackend> make_ota_backend();

}  // namespace ota
}  // namespace esphome
