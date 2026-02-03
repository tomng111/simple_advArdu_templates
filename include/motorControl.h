#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Motor control pins
#define PWM 9 // ORANGE
#define IN2 8 // IN2
#define IN1 7 // IN1

// Function prototypes
void setMotor(int dir, int pwmVal);

#endif
