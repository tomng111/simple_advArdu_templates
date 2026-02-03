#include "motorControl.h"

void setMotor(int dir, int pwmVal) 
{
    analogWrite(PWM, pwmVal);
    if (dir == 1) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    } else if (dir == -1) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
    }
}
