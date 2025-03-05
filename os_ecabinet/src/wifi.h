#ifndef WIFI_H
#include <M5Unified.h>
#include <WiFi.h>
#include <WiFiManager.h>
#define WIFI_H
#endif

void wifi_setup();
void configModeCallback (WiFiManager *myWiFiManager);