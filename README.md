# ESP Light Controller

This project uses the C Light Controller and creats an ESP specific LightSwitch and list of Lights.

## Install
https://github.com/kesslerpillar/esp-light-controller/wiki

## Pre-Build
1. The following config settings are not stored with the project in Github. You'll have to update the sdkconfig file to have these settings applied to the device.
	1. CONFIG_ESP_WIFI_SSID
	2. CONFIG_ESP_WIFI_PASSWORD
	3. CONFIG_MQTT_BROKER_URL

## Build
1. run `idf.py build`
1. run `idf.py menuconfig`
1. Hook up the device to a USB port
1. run `idf.py flash monitor`
