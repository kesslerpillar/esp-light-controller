set(COMPONENT_SRCS
        "light_main.cpp"
        "service/wifi_service.cpp"
        "lib/LightController.cpp"
        "ButtonLightSwitch.cpp"
        "PhysicalLight.cpp"
        "WebLight.cpp"
        "MqttLight.cpp"
        "service/MqttService.cpp")

set(COMPONENT_ADD_INCLUDEDIRS "." "lib")

register_component()
