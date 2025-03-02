#ifndef LUMINOSITY_H
#define LUMINOSITY_H
#include "main.h"
#define LIGHT_SENSOR_PIN  35  // ESP32 pin GPIO35 (ADC0) connected to light sensor
#endif

void get_luminosity(int *luminosity_value, bool print_on_serial);