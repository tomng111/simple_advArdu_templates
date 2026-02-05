#include<Servo.h>
Servo motor;

int aPin = A0;
int winkel = 0;

void setup(){
  motor.attach(9);
  motor.write(0);
  Serial.begin(9600);
}

void loop(){
  //int analogwert = analogRead(aPin);
  //winkel = map(analogwert, 0, 1023, 0, 180);
  //Serial.println(map(analogwert, 0, 1023, 0, 180));
  winkel = map(analogRead(aPin), 0, 1023, 0, 180);
  motor.write(winkel);
}
