#include <Arduino.h>
#include "../lib/Servo/Servo.h"
#include "../lib/Keypad/Keypad.h"

Servo KluisjeA;
Servo KluisjeB;
int geslotenA = 140;
int openA = 42;
int geslotenB = 161;
int openB = 90;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10};  //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6};  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String wachtwoordA[] = { "-0000", "-1234", "-4865200" };
String wachtwoordB[] = { "-1111", "-4321", "-4802799" };
String keyCombinatie = "-";

int wachtwoordCheck = 0;

// Dit is de setup, de eerste code die uitgevoerd wordt
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");
  KluisjeA.attach(2);
  KluisjeB.attach(3);
  KluisjeA.write(geslotenA);
  KluisjeB.write(geslotenB);
}



// draai de Servo horizontaal
void SluitKluis(Servo kluis, int slotkluis){
    delay(500);
    kluis.write(slotkluis);
    keyCombinatie = "-";
    Serial.println("");
}



// draai de Servo verticaal 
void OpenKluis(Servo kluis, int slotkluis){
  delay(500);
  kluis.write(slotkluis);
  keyCombinatie = "-";
  Serial.println("");
}



void WachtwoordCheck(){
  if (keyCombinatie == wachtwoordA[wachtwoordCheck])
    {
      OpenKluis(KluisjeA, openA);
    }
  else if (keyCombinatie == wachtwoordB[wachtwoordCheck])
    {
      OpenKluis(KluisjeB, openB);
    }

  while (keyCombinatie != wachtwoordA[wachtwoordCheck] && keyCombinatie != wachtwoordB[wachtwoordCheck])
    {
      wachtwoordCheck++;
      if (keyCombinatie == wachtwoordA[wachtwoordCheck])
      {
        OpenKluis(KluisjeA, openA);
      }
      if (keyCombinatie == wachtwoordB[wachtwoordCheck])
      {
        OpenKluis(KluisjeB, openB);
      }
      else if (wachtwoordA[wachtwoordCheck] == "" && wachtwoordB[wachtwoordCheck] == "")
      {
        wachtwoordCheck = 0;
        keyCombinatie = "-";
        Serial.println("");
        break;
      }
    }
}



void CheckKey(char leesKey){
  // Van if statement een switch gemaakt. 
  switch (leesKey)
  {
  case '#':
    Serial.println(leesKey);
    SluitKluis(KluisjeA, geslotenA);
    SluitKluis(KluisjeB, geslotenB);
    break;
  case '*':
    Serial.println(leesKey);
    WachtwoordCheck();
    break;
  case 'A':
    Serial.println(leesKey);
    SluitKluis(KluisjeA, geslotenA);
    break;
  case 'B':
    Serial.println(leesKey);
    SluitKluis(KluisjeB, geslotenB);
    break;
  case 'C':
    Serial.println(leesKey);
    SluitKluis(KluisjeA, geslotenA);
    break;
  case 'D':
    Serial.println(leesKey);
    SluitKluis(KluisjeB, geslotenB);
    break;
  default:
    Serial.print(leesKey);
    keyCombinatie += leesKey;
    break;
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  char leesKey = customKeypad.getKey();
  CheckKey(leesKey);
} 
