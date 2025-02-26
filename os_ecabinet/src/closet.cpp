#include "closet.h"
#include "mqtt.h"

#include <M5Unified.h>

int get_placard_id() {
  return 1; // A modifier pour chaque placard
}

void handle_buttonA() {
  Serial.println("Bouton A");
  mqtt_publish("placard/0/status","OK");
  //show_good_placement(0);
}

void handle_buttonB() {
  mqtt_publish("placard/0/status","NOK");
  mqtt_publish("placard/1/status","SIGNAL");
  //show_bad_placement(1);
}

void handle_buttonC() {
  //show_removal(2);
  mqtt_publish("placard/1/status","NOK");
  mqtt_publish("placard/0/status","SIGNAL");
}