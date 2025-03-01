#include "closet.h"


int get_cabinet_id() {
  return 1; // A modifier pour chaque placard
}

//fake received message
void handle_buttonA() {
  Serial.println("Bouton A");
  mqtt_publish("cabinet/1/status","OK");
}

void handle_buttonB() {
  mqtt_publish("cabinet/0/status","NOK");
  mqtt_publish("cabinet/1/status","SIGNAL");
}

void handle_buttonC() {
  mqtt_publish("cabinet/1/status","NOK");
  mqtt_publish("cabinet/0/status","SIGNAL");
}