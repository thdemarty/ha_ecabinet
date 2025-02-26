
#ifndef MQTT_H
#define MQTT_H
#include <PubSubClient.h>
#endif

void mqtt_loop();
void mqtt_setup();
void mqtt_reconnect();
void mqtt_publish(char* topic, char* payload);
void mqtt_subscribe(char* topic);
void mqtt_callback(char* topic, byte* payload, unsigned int length);