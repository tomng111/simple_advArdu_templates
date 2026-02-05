#include <Servo.h>
Servo motor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor.attach(9);
  motor.write(0); // Initial angle
}

void loop() {
  // put your main code here, to run repeatedly:
  String daten = "";
  while(Serial.available()>0){
    char r = Serial.read();
    daten += r;
    delay(5);
  }
  daten.trim(); // Blank space
  // Servos
  if(daten != ""){
    motor.write(daten.toInt());
    daten = "";
  }
}
