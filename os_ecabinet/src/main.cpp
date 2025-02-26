// Projet IoT - Placard connecté

#include <M5Unified.h>
#include <FastLED.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "led_matrix.h"
// #include "closet.h"
// #include "rfid.h"
#include "wifi.h"
#include "mqtt.h"




void setup()
{
    M5.begin();
    // M5.Ex_I2C.begin(I2C_PORT, I2C_SDA, I2C_SCL);

    Serial.begin(115200);
    // Display initialization
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("e-Shelf");
    
    // Setups    
    leds_matrix_setup();
    // rfid_setup();
    wifi_setup();
    mqtt_setup();
}

void loop()
{
    // leds_loop();
    mqtt_loop();
    M5.update();

    // Button handling
    if (M5.BtnA.wasClicked()) {
        // handle_buttonA();
    } else if (M5.BtnB.wasClicked()) {
        // handle_buttonB();
    } else if (M5.BtnC.wasClicked()) {
        // handle_buttonC();
    }
    
    delay(10);
}