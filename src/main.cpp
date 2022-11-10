#include <Arduino.h>
#include "../lib/Servo/Servo.h"

Servo servo;
int gesloten = 140;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");
  servo.attach(3);
  servo.write(gesloten);
}

void SluitKluis(){
  servo.write(140);
  delay(800);
}
void OpenKluis(){
  servo.write(42);
  delay(800);
}

void loop() {
  // put your main code here, to run repeatedly:
  SluitKluis();
  OpenKluis();
} 
