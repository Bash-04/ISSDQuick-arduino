#include <Arduino.h>
#include "../lib/Servo/Servo.h"
#include "../lib/Keypad/Keypad.h"

Servo servo;
int gesloten = 140;

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

String wachtwoord = "0000";
String codeNummer;

// int wachtwoordCheck = 0;

// Dit is de setup, de eerste code die uitgevoerd wordt
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello World");
  servo.attach(3);
  servo.write(gesloten);
}



// draai de Servo 140 graden betekent dat deze horizontaal staat gedraait
void SluitKluis(char leesKey){
  if (leesKey == '#')
  {
    servo.write(140);
    delay(800);
    codeNummer = "";
    Serial.println("");
  }
}



// draai de Servo 140 graden betekent dat deze verticaal staat gedraait
void OpenKluis(){
  servo.write(42);
  delay(800);
}



// De functie om de ingedrukte key te printen en in de var "CodeStudentnummer" te plaatsen
void codeStudentnummer(char leesKey){
  if (leesKey){
    Serial.print(leesKey);
    codeNummer += leesKey;
  }

  //array maken van wachtwoord als je het de loop weer uncomment. ook de "wachtwoordCheck" variable bovenaan uncommenten.
  // while (codeNummer != wachtwoord[wachtwoordCheck])
  // {
  //   if (codeNummer == wachtwoord[wachtwoordCheck])
  //   {
    if (codeNummer == wachtwoord)
    {
      delay(500);
      OpenKluis();
      codeNummer = "";
      Serial.println("");
    }
    
  //   }
  //   wachtwoordCheck++;
  //   if (wachtwoord[wachtwoordCheck] == "")
  //   {
  //     wachtwoordCheck = 0;
  //     break;
  //   }
  // }
}



void loop() {
  // put your main code here, to run repeatedly:
  char leesKey = customKeypad.getKey();
  codeStudentnummer(leesKey);
  SluitKluis(leesKey);
} 
