#include<TimerOne.h>
// control PINs from left motor
// OUT1 - SCHWARZ
// OUT2 - GRUEN
#define ENA 9 // L298||ENA - ORANGE
#define IN1 7 // L298||IN1 - ROT
#define IN2 8 // L298||IN2 - BRAUN
#define ENCA 2 // ENCODER||CHANNEL A - GELB - VOR
#define ENCB 3 // ENCODER||CHANNEL B - WEISS - ZURUECK
// PID parameters
#define Kp 0.01
#define Kd 0.0002
#define Ki 0.04
// variables
int dir; // direction
float T, puls; // T = sampled time   
float gesch, sollwertGesch; 
double e, e1, e2; // e(k), e(k-1), e(k-2)
double alpha, beta, gamma;
double istwert, naechIstwert; 
// MAIN
void setup(){
  // put your setup code here, to run once:
  // ENCODER||GND - ORANGE
  // ENCODER||3.3V PIN - ROT
  pinMode(ENCA, INPUT_PULLUP); // Channel A
  pinMode(ENCB, INPUT_PULLUP); // Channel B
  pinMode(ENA, OUTPUT); 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz - MEGA2560
  sollwertGesch = 150; gesch = 0;
  e = 0; e1 = 0; e2 = 0;
  istwert = 0; naechIstwert = 0;
  T = 0.01; // 10 ms
  Serial.begin(9600);
  attachInterrupt(0, pulsZaehlung, FALLING);
  Timer1.initialize(10000); // 10 ms
  Timer1.attachInterrupt(PIDFunk);
}
void loop(){
  // put your main code here, to run repeatedly:
  // Command from keyboard
  if(Serial.available()){
    char befehl = Serial.read();
    if(befehl == 'v') dir = 1; // Vor
    if(befehl == 'z') dir = -1; // Zurueck
    if(befehl == 's') dir = 0; // Stop
  }
  Serial.print(sollwertGesch); Serial.print(" ");
  Serial.print(gesch); Serial.println();
}
void pulsZaehlung()
{
  if (dir == 1){ // Turn one way: use channel A
    if(digitalRead(ENCA) == LOW) puls++;
    else  puls--;
  }
  else if (dir == -1){ // Turn the other way: use channel B
    if(digitalRead(ENCB) == LOW) puls++;
    else  puls--;
  }
}
void PIDFunk()
{ 
  gesch = ((puls/234.3)*(1/T)*60); // 21.3:1 x 11 pulses = 234.3 pulses/round - GA25370-280RPM
  puls = 0;
  // error
  e = sollwertGesch - gesch;
  // discrete PID function
  alpha = 2*T*Kp + Ki*T*T + 2*Kd;
  beta = T*T*Ki - 4*Kd - 2*T*Kp;
  gamma = 2*Kd;
  istwert = (alpha*e + beta*e1 + gamma*e2 + 2*T*naechIstwert)/(2*T);
  naechIstwert = istwert;
  // update
  e2 = e1;
  e1 = e;
  // condition
  if(istwert > 255) istwert = 255;
  // direction
  if(dir == 1){ 
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
  }
  else if(dir == -1){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
  }
  else{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);    
  }
  analogWrite(ENA, abs(istwert));
}
