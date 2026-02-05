#define led 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
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
  // LED
  if(daten == "e1")  digitalWrite(led, HIGH);
  if(daten == "a1")  digitalWrite(led, LOW);
}
