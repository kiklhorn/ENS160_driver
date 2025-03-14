#include "esphome.h"
#include "ScioSense_ENS160.h"

// Requires this lib installed: $ platformio lib --global install "Adafruit BusIO"
// based on https://github.com/adafruit/Adafruit_VEML7700/blob/master/examples/veml7700_test/veml7700_test.ino


class ENS160Sensor : public PollingComponent, public Sensor {
public:
ScioSense_ENS160 ens160 = ScioSense_ENS160();

Sensor *AQI_sensor = new Sensor();
Sensor *TVOC_sensor = new Sensor();
Sensor *eCO2_sensor = new Sensor();

ENS160Sensor() : PollingComponent(15000) {}
void setup() override {
    Wire.begin();
    ens160.begin();
    ens160.setMode(ENS160_OPMODE_STD);
    ens160.measure(0);
}

void update() override {
    float aqi = ens160.getAQI();
    float tvoc = ens160.getTVOC();
    float eco2 = ens160.geteCO2();
    ESP_LOGD("ENS160", "The value of sensor AQI is: %.0f", aqi);
    ESP_LOGD("ENS160", "The value of sensor TVOC is: %.0f", tvoc);
    ESP_LOGD("ENS160", "The value of sensor eCO2 is: %.0f", eco2);
    AQI_sensor->publish_state(aqi);
    TVOC_sensor->publish_state(tvoc);
    eCO2_sensor->publish_state(eco2);
}
};
