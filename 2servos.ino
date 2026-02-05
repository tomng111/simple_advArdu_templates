#include <Servo.h>
Servo motor1;
Servo motor2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motor1.attach(8);
  motor2.attach(9);
  motor1.write(0);
  motor2.write(0);
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
  String winkel1 = daten.substring(0, index);
  String winkel2 = daten.substring(index + 1);
  // Servos
  if(daten != ""){
    motor1.write(winkel1.toInt());
    motor2.write(winkel2.toInt());
    daten = "";
  }
}
