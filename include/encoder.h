#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

// Encoder pins
#define ENCODER_1A 2 // GELB - CHANNEL A
#define ENCODER_1B 3 // WEISS - CHANNEL B

// Global variables
extern volatile int posi;

// Function prototypes
void encoder1_isr();

#endif
