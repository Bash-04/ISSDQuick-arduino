#include <Arduino.h>
#include "Servo.h"
#include "Keypad.h"

Servo KluisjeA;
Servo KluisjeB;
int geslotenA = 140;
int openA = 42;
int geslotenB = 180;
int openB = 110;

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

String wachtwoordA[] = { "-24", "-0000" , "-1234" };
String wachtwoordB[] = { "-1111", "-4321" };
String keyCombinatie = "-";

int wachtwoordCheck = 0;

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
  if (keyCombinatie == wachtwoordA[wachtwoordCheck])
    {
      Serial.println("if - kluisA geopent");
      OpenKluis(KluisjeA, openA);
      return;
    }
  if (keyCombinatie == wachtwoordB[wachtwoordCheck])
    {
      Serial.println("if - kluisB geopent");
      OpenKluis(KluisjeB, openB);
      return;
    }

  while (keyCombinatie != wachtwoordA[wachtwoordCheck] && keyCombinatie != wachtwoordB[wachtwoordCheck])
    {
      wachtwoordCheck++;
      if (keyCombinatie == wachtwoordA[wachtwoordCheck])
      {
        Serial.println("loop - kluisA geopent");
        OpenKluis(KluisjeA, openA);
      }
      else if (keyCombinatie == wachtwoordB[wachtwoordCheck])
      {
        Serial.println("loop - kluisB geopent");
        OpenKluis(KluisjeB, openB);
      }
      else if (wachtwoordA[wachtwoordCheck] == "" && wachtwoordB[wachtwoordCheck] == "")
      {
        wachtwoordCheck = 0;
        keyCombinatie = "-";
        Serial.println("wachtwoord incorrect");
        break;
      }
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
    WachtwoordCheck();
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

}



void loop() {
  // put your main code here, to run repeatedly:
  char leesKey = customKeypad.getKey();
  CheckKey(leesKey);
  consoleReadWrite();
}
