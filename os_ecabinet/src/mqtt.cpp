#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

IPAddress server_mqtt(192, 168, 0, 90);
const int mqtt_port = 1883;

void subscribe_mqtt_topic(char *topic)
{
  Serial.print("Subscribe to ");
  Serial.println(topic);
  client.subscribe(topic);
}

void mqtt_reconnect()
{
  while (!client.connected())
  {
    char client_id[5];
    int cabinet_id = get_cabinet_id();
    sprintf(client_id, "m5-%d", cabinet_id);
    if (client.connect(client_id))
    {
      char topic[19];

      // cabinet reconnect to his status topic
      sprintf(topic, "cabinet/%d/status", cabinet_id);
      subscribe_mqtt_topic(topic);
    }
    else
    {
      Serial.print("echec, code erreur= ");
      Serial.println(client.state());
      Serial.println("nouvel essai dans 5s");
      delay(5000);
    }
  }
}

void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  std::string topic_str(topic);
  std::string msg((char *)payload, length);
  Serial.print("Msg reçu (topic puis msg): ");
  Serial.println(topic_str.c_str());
  Serial.println(msg.c_str());
  std::string statusTopic = std::string("cabinet/") + std::to_string(get_cabinet_id()) + std::string("/status");
  if (topic_str == statusTopic)
  {
    int i = get_cabinet_id();
    Serial.print("Cabinet: ");
    Serial.println(get_cabinet_id());
    if (msg == "OK")
    {
      show_good_placement(i);
    }
    else if (msg == "NOK")
    {
      show_bad_placement(i);
    }
    else if (msg == "SIGNAL")
    {
      signal_placement(i);
    }
  }
  else
  {
    Serial.print("erreur, subscribe du topic non traité: ");
    Serial.println(topic_str.c_str());
  }
}

void mqtt_loop()
{
  if (!client.connected())
  {
    mqtt_reconnect();
  }
  client.loop();
}

void mqtt_publish(char *topic, char *payload)
{
  client.publish(topic, payload);
}

void mqtt_setup()
{
  client.setServer(server_mqtt, mqtt_port);
  client.setCallback(mqtt_callback);
  mqtt_reconnect();
}
