#include <lib/LightController.h>
#include "nvs_flash.h"
#include "esp_event.h"
#include "service/wifi_service.h"
#include "PhysicalLight.h"
#include "WebLight.h"
#include "ButtonLightSwitch.h"
#include <vector>

using namespace std;

unique_ptr<LightController> getLightController();

unique_ptr<LightController> getLightController() {
    vector<shared_ptr<Light> > lights{(Light *) new PhysicalLight(), (Light *) new WebLight()};
    shared_ptr<LightSwitch> lightSwitch(new ButtonLightSwitch());
    unique_ptr<LightController> lightController(new LightController(lightSwitch, lights));
    return lightController;
}

extern "C" {

void app_main()
{
    setupWiFi();
    unique_ptr<LightController> lightController = getLightController();

    while(1) {
        lightController->update();
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

}