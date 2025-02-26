#include <M5Unified.h>
#include <WiFi.h>

const char * ssid = "Cat S75";
const char * password = "c7mjx6jau8q64ws";

void wifi_setup() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        M5.Lcd.print(".");
    }

    M5.Lcd.println("");
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);

    M5.Lcd.println("SSID: " + String(ssid));
    M5.Lcd.println("IP: " + WiFi.localIP().toString());
    M5.Lcd.println("MAC: " + WiFi.macAddress());
}
