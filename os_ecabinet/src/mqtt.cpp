#include <WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>
#include "led_matrix.h"


WiFiClient espClient;
PubSubClient client(espClient);

const char *mqtt_server = "192.168.31.201";
const int mqtt_port = 1883;

void mqtt_reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client"))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
    }
  }
}
void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, "rgb/command/shelf1") == 0)
  {
    Serial.println("Shelf 1");
    light_quarter(0, CRGB::Green);
  }
  else if (strcmp(topic, "rgb/command/shelf2") == 0)
  {
    Serial.println("Shelf 2");
    light_quarter(1, CRGB::Green);
  }
  else if (strcmp(topic, "rgb/command/shelf3") == 0)
  {
    Serial.println("Shelf 3");
    light_quarter(2, CRGB::Green);
  }
  else if (strcmp(topic, "rgb/command/absent") == 0)
  {
    Serial.println("Shelf 4");
    light_quarter(3, CRGB::Red);
  } else {
      std::string topic_str(topic);
      std::string msg((char*) payload, length);
      for (int i = 0; i<NB_PLACARDS; i++){
        std::string placardString = "placard/" + std::to_string(i) + "/status";
        if (topic_str == placardString){
          Serial.print("Placard ");
          Serial.println(i);
          if (msg == "OK") {
              show_good_placement(i);
          } else if (msg == "NOK") {
              show_bad_placement(i);
          }else if (msg == "SIGNAL"){
              signal_placement(i);
          }
        break;
        }
      } 
  }
}

void mqtt_loop()
{
  client.loop();
}

void mqtt_subscribe(const char *topic)
{
  client.subscribe(topic);
}

void mqtt_publish(char *topic, char *payload)
{
  client.publish(topic, payload);
}

void mqtt_setup()
{
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqtt_callback);
  mqtt_reconnect();

  mqtt_subscribe("rgb/command/shelf1");
  mqtt_subscribe("rgb/command/shelf2");
  mqtt_subscribe("rgb/command/shelf3");
  mqtt_subscribe("rgb/command/absent");
}

