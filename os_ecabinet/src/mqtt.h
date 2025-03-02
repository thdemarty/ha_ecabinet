#ifndef MQTT_H
#define MQTT_H
#include "main.h"
#include "closet.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>
#include "led_matrix.h"
#include <string>
#endif

void subscribe_mqtt_topic(char *topic);
void mqtt_loop();
void mqtt_setup();
void mqtt_reconnect();
void mqtt_publish(char* topic, char* payload);
void mqtt_callback(char* topic, byte* payload, unsigned int length);