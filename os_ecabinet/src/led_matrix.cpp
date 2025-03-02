#include "led_matrix.h"

CRGB leds[NUM_LEDS];
std::map<int, unsigned long> durations;
int leds_par_placard = MATRIX_SIZE / NB_PLACARDS;


void leds_matrix_setup() {
    gpio_reset_pin(MATRIX_SIGNAL_PIN);
    pinMode(MY_DATA_PIN, OUTPUT);
    digitalWrite(MY_DATA_PIN, LOW);
    FastLED.addLeds<NEOPIXEL, MY_DATA_PIN>(leds, NUM_LEDS);
    FastLED.showColor(CRGB::Black);
    FastLED.setBrightness(10);
}


void set_leds_color(int placard, CRGB color) {
    int first = placard * leds_par_placard;
    for (int x = first; x < first + leds_par_placard; x++) {
        for (int y = first; y < first + leds_par_placard; y++) {
            leds[x + y*MATRIX_SIZE] = color;
        }
    }
    FastLED.show();
    
}


void light_quarter(int quarter, CRGB color) {
    Serial.println("Lighting quarter " + String(quarter) + " with color " + String(color.r) + " " + String(color.g) + " " + String(color.b));
    // Define LED indices for each quarter
    const int quarterLEDs[4][16] = {
        {0, 1, 2, 3, 8, 9, 10, 11, 16, 17, 18, 19, 24, 25, 26, 27},         // Quart Haut Gauche
        {4, 5, 6, 7, 12, 13, 14, 15, 20, 21, 22, 23, 28, 29, 30, 31},       // Quart Haut Droite
        {32, 33, 34, 35, 40, 41, 42, 43, 48, 49, 50, 51, 56, 57, 58, 59},   // Quart Bas Gauche
        {36, 37, 38, 39, 44, 45, 46, 47, 52, 53, 54, 55, 60, 61, 62, 63}    // Quart Bas Droite
    };
    
    FastLED.clear();

    for (int i = 0; i < 16; i++) {
        leds[quarterLEDs[quarter][i]] = color;
    }

    FastLED.setBrightness(12);

    FastLED.show(); 
}

void leds_loop() {
    for (auto itr = durations.cbegin(); itr != durations.cend();) {
        if (itr->second < millis()) {
            // fin de la durée de la LED
            set_leds_color(itr->first, CRGB::Black);
            itr = durations.erase(itr);
        } else {
            itr = std::next(itr);
        }
    }
}

void show_good_placement(int placard) {
    set_leds_color(placard, CRGB::Green);
    durations[placard] = millis() + 2000;
}

void show_bad_placement(int placard) {
    set_leds_color(placard, CRGB::Red);
    durations[placard] = millis() + 2000;
}

void show_removal(int placard) {
    set_leds_color(placard, CRGB::Blue);
    durations[placard] = millis() + 2000;
}

void signal_placement(int placard) {
    set_leds_color(placard, CRGB::Purple);
    durations[placard] = millis() + 2000;
}
