#include "ota_backend.h"
#ifdef USE_ARDUINO
#ifdef USE_ESP8266
#include "ota_backend_arduino_esp8266.h"
#endif  // USE_ESP8266
#ifdef USE_ESP32
#include "ota_backend_arduino_esp32.h"
#endif  // USE_ESP32
#endif  // USE_ARDUINO
#ifdef USE_ESP_IDF
#include "ota_backend_esp_idf.h"
#endif  // USE_ESP_IDF
#ifdef USE_RP2040
#include "ota_backend_arduino_rp2040.h"
#endif  // USE_RP2040
#ifdef USE_LIBRETINY
#include "ota_backend_arduino_libretiny.h"
#endif

namespace esphome {
namespace ota {

std::unique_ptr<ota::OTABackend> make_ota_backend() {
#ifdef USE_ARDUINO
#ifdef USE_ESP8266
  return make_unique<ota::ArduinoESP8266OTABackend>();
#endif  // USE_ESP8266
#ifdef USE_ESP32
  return make_unique<ota::ArduinoESP32OTABackend>();
#endif  // USE_ESP32
#endif  // USE_ARDUINO
#ifdef USE_ESP_IDF
  return make_unique<ota::IDFOTABackend>();
#endif  // USE_ESP_IDF
#ifdef USE_RP2040
  return make_unique<ota::ArduinoRP2040OTABackend>();
#endif  // USE_RP2040
#ifdef USE_LIBRETINY
  return make_unique<ota::ArduinoLibreTinyOTABackend>();
#endif
}

}  // namespace ota
}  // namespace esphome
