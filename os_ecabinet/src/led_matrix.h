#ifndef LED_MATRIX_H
#define LED_MATRIX_H
#include <FastLED.h>
#include <crgb.h>
#include "main.h"
#include <M5Unified.h>
#include <map>
#define MATRIX_SIGNAL_PIN    GPIO_NUM_12
#define MY_DATA_PIN 12
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define MATRIX_SIZE 8
#define NUM_LEDS 64
#endif

void leds_matrix_setup();
void light_quarter(int quarter, CRGB color);
void set_leds_color(int placard, CRGB color);
/// @brief used to make animations
void leds_loop();
void show_good_placement(int placard);
void show_bad_placement(int placard);
void show_removal(int placard);
void signal_placement(int placard);