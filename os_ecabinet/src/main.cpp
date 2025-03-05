#include "main.h"

uint32_t now;
static byte rf_uid[500] = {0};
static byte rf_length = 0;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    
    // Display initialization
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0);
    // M5.Lcd.println(get_cabinet_id());

    // Setups
    
    wifi_setup();
    mqtt_setup();
    
    // Checks for

    leds_matrix_setup();
    rfid_setup();

}

void loop()
{
    leds_loop();
    mqtt_loop();
    // static int analog_val_lum;
    // if (millis() - now > 1000)
    // {

    //     get_luminosity(&analog_val_lum, 0);
    //     if (analog_val_lum < 2000)
    //     {
    //         // RFID uniquement si le placard est ouvert
    //         loop_UIDs(rf_uid, &rf_length);
    //     }
    //     now = millis();
    // }

    M5.update();
    if (M5.BtnA.wasClicked())
    {
        handle_buttonA();
    }
    else if (M5.BtnB.wasClicked())
    {
        handle_buttonB();
    }
    else if (M5.BtnC.wasClicked())
    {
        handle_buttonC();
    }
}
