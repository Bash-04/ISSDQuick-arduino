#include <Arduino.h>
#include "Servo.h"
#include "Keypad.h"

Servo KluisjeA;
Servo KluisjeB;
int geslotenA = 140;
int openA = 42;
int geslotenB = 188;
int openB = 95;

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

String wachtwoordA = "-24";
String wachtwoordB = "-0";
String keyCombinatie = "-";

String productA = "";
String productB = "";
String gereserveerdProductA = "";
String gereserveerdProductB = "";
String studentnummer = "";

// Dit is de setup, de eerste code die uitgevoerd wordt
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");
  KluisjeA.attach(4);
  KluisjeB.attach(5);
  KluisjeA.write(geslotenA);
  KluisjeB.write(geslotenB);
}



// draai de Servo horizontaal om de kluisdeur te sluiten
void SluitKluis(Servo kluis, int slotkluis){
  delay(500);
  kluis.write(slotkluis);
  keyCombinatie = "-";
  Serial.println("Er is een kluis gesloten");
  Serial.println("");
}



// draai de Servo verticaal om de kluisdeur te kunnen openen
void OpenKluis(Servo kluis, int slotkluis){
  delay(500);
  kluis.write(slotkluis);
  keyCombinatie = "-";
  Serial.println("Er is een kluis geopent");
  Serial.println("");
}



void WachtwoordCheck(){
  // deze functie checkt of de ingevoerde code klopt met een wachtwoord van een kluisje
  Serial.println("wwcheck: " + keyCombinatie + ", " + wachtwoordA);
  if (keyCombinatie == wachtwoordA)
    {
      Serial.println("if - kluisA geopent");
      OpenKluis(KluisjeA, openA);
    }
  else if (keyCombinatie == wachtwoordB)
    {
      Serial.println("if - kluisB geopent");
      OpenKluis(KluisjeB, openB);
    }
  else{
      keyCombinatie = "-";
      Serial.println("wachtwoord incorrect");
  }
}



void CheckKey(char leesKey){
  // Deze if statement zorgt ervoor dat de juiste functie wordt uitgevoerd bij de klik op een bepaalde key
  if (leesKey == '#')
  {
    Serial.println(leesKey);
    SluitKluis(KluisjeA, geslotenA);
    SluitKluis(KluisjeB, geslotenB);
    Serial.println("Alle kluisjes zijn gesloten");
    Serial.println("");
  }
  else if (leesKey == '*')
  {
    Serial.println(leesKey);
    Serial.println("Voor wA: " + wachtwoordA);
    Serial.println("Voor keyCombi: " + keyCombinatie);
    WachtwoordCheck();
    Serial.println("Na wA: " + wachtwoordA);
    Serial.println("Na keyCombi: " + keyCombinatie);
  }
  else if (leesKey == 'A')
  {
    Serial.println(leesKey);
    Serial.println("KluisA gesloten");
    SluitKluis(KluisjeA, geslotenA);
  }
  else if (leesKey == 'B')
  {
    Serial.println(leesKey);
    Serial.println("KluisB gesloten");
    SluitKluis(KluisjeB, geslotenB);
  }
  else if (leesKey == 'C')
  {
    Serial.println(leesKey);
    Serial.println("KluisA gesloten");
    SluitKluis(KluisjeA, geslotenA);
  }
  else if (leesKey == 'D')
  {
    Serial.println(leesKey);
    Serial.println("KluisB gesloten");
    SluitKluis(KluisjeB, geslotenB);
  }
  else if (leesKey)
  {
    Serial.print(leesKey);
    keyCombinatie += leesKey;
  }
}



void consoleReadWrite(){
  if (Serial.available() > 0) { 
    char received = Serial.read();
    if (received == '\n')
    {
      Serial.println(keyCombinatie);
      wachtwoordA = "" + keyCombinatie;
      Serial.println(wachtwoordA);
      keyCombinatie = "-";
    }
    else
    {
      keyCombinatie += received;
    }
  }
}



void loop() {
  // put your main code here, to run repeatedly:
  char leesKey = customKeypad.getKey();
  CheckKey(leesKey);
  consoleReadWrite();
}
