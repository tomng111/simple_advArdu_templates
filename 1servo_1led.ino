#include <Servo.h>
#define led 13
Servo motor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor.attach(9);
  motor.write(0);
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
  int index = daten.indexOf(',');
  String winkel = daten.substring(0, index);
  String befehl = daten.substring(index + 1);
  // Servo & LED
  if(daten != ""){
    motor.write(winkel.toInt());
    if(befehl == "e1") digitalWrite(led, HIGH);
    if(befehl == "a1") digitalWrite(led, LOW);
    daten = "";
  }
}
