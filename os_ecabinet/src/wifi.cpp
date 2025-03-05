#include "wifi.h"
#include <WiFiManager.h>

void wifi_setup()
{
    WiFiManager wm;
    wm.setAPCallback(configModeCallback);

    // Extra parameters that could be configured through the portal
    // WiFiManagerParameter config_mqtt_ipv4("mqtt_ipv4", "mqtt ipv4", "", 40);
    // WiFiManagerParameter config_mqtt_port("mqtt_port", "mqtt port", "", 6);
    // WiFiManagerParameter config_mqtt_user("mqtt_user", "mqtt user", "", 20);
    // WiFiManagerParameter config_mqtt_pass("mqtt_pass", "mqtt pass", "", 20);
    
    // wm.addParameter(&config_mqtt_ipv4);
    // wm.addParameter(&config_mqtt_port);
    // wm.addParameter(&config_mqtt_user);
    // wm.addParameter(&config_mqtt_pass);


    // If the device as already been connected to a network, it will try to connect to it.
    // otherwise, it will create a new wifi-network to connect-to with a generated SSID 
    // like ESP and chipID 
    bool res = wm.autoConnect();

    if (!res) {
        M5.Lcd.println("Failed to connect");
    } else {
        M5.Lcd.printf("Connected to %s\n", WiFi.SSID().c_str());
        M5.Lcd.println(WiFi.localIP());
        M5.Lcd.println(WiFi.macAddress());
    }
}


/**
 * Callback function that is called when the device is in configuration mode
 * (ie. when the device is not connected to a known network and is in AP mode)
 */
void configModeCallback (WiFiManager *myWiFiManager) {
    M5.Lcd.println("  Entered in config mode\n==========================");
    M5.Lcd.println("Connect to access point\n\n");
    M5.Lcd.setTextColor(YELLOW);
    
    M5.Lcd.println(myWiFiManager->getConfigPortalSSID());
    M5.Lcd.setTextColor(WHITE);
    
    M5.Lcd.println("\nand navigate to\n");
    M5.Lcd.println(WiFi.softAPIP());
  }