#include "luminosity.h"

/// @brief Provides the luminosity value using analog read from the
/// photoresistor
/// @param brightness
/// @param print_on_serial
void get_luminosity(int *luminosity_value, bool print_on_serial) {
  // TODO
  // Placer ici le code pour obtenir la valeur de luminosité à partir d'une
  // lecture analogique sur le pin défini dans le header par LIGHT_SENSOR_PIN
  *luminosity_value = analogRead(LIGHT_SENSOR_PIN);
}
