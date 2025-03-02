#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <M5Unified.h>
#include <FastLED.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "led_matrix.h"
#include "rfid.h"
#include "wifi.h"
#include "mqtt.h"
#include "luminosity.h"
#include "closet.h"
#endif

#define I2C_PORT I2C_NUM_0
#define I2C_SDA 21
#define I2C_SCL 22
#define NB_PLACARDS 3