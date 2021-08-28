#include <OneButton.h>
#include <LiquidCrystal_I2C_JHD1214.h>
LiquidCrystal_I2C lcd(0x7C >> 1, 16, 2);
#include <Wire.h>
#define PRERIS 2
#define ESTRUDE 3
#define TARGET 4
#define MOVXYZ 5
#define PRINT 6
#define PAUSE 7

OneButton button(10, true);

int stato = 0;
int key_flag = 0;
bool cambio = false;


void handleClick() {
  if (key_flag == 0) {
    key_flag = 5;
  }
  else if (key_flag == 5) {
    key_flag = 6;
  }
  else if ( key_flag == 1 || key_flag == 2 || key_flag == 3 || key_flag == 4 || key_flag == 6) {
   key_flag = 0;
    stato = 0;
  }
  cambio = true;
}

void receiveEvent(int howMany) {
  key_flag = Wire.read();
  Serial.print("received: ");
  Serial.println(key_flag);
  cambio = true;
}

void sendEvent() {
  Wire.beginTransmission(9);
  Wire.write(stato);
  Wire.endTransmission();
  Serial.print("sent: ");
  Serial.println(stato);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PRERIS, OUTPUT); // PRERISCALDAMENTO
  pinMode(ESTRUDE, OUTPUT); // ESTRUSIONE E RITRAZIONE
  pinMode(TARGET, OUTPUT); // IN TEMPERATURA
  pinMode(MOVXYZ, OUTPUT); // ASSI IN MOVIMENTO
  pinMode(PRINT, OUTPUT); // IN STAMPA
  pinMode(PAUSE, OUTPUT); // IN PAUSA

  button.attachClick(handleClick);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("Welcome MASTER");

  Serial.begin(9600);
  Wire.begin(0);
  Wire.onReceive(receiveEvent);
  Serial.println("Welcome to MASTER");

}

void loop() {

  if (cambio == true) {
    lcd.clear();
    if   (key_flag == 1) {
      lcd.setCursor(0, 0);
      lcd.print("BUT HOME wait...");
      lcd.setCursor(0, 1);
      lcd.print("Z HOME");
      digitalWrite(MOVXYZ, HIGH);
      delay(2000);
      stato = 0;
      key_flag = 0;
      digitalWrite(MOVXYZ, LOW);
          }
    else if   (key_flag == 2) {
      lcd.setCursor(0, 0);
      lcd.print("BUT MINUS wait...");
      lcd.setCursor(0, 1);
      lcd.print("preheating");
      digitalWrite(PRERIS, HIGH);
      stato = 1;
      delay(2000);
      digitalWrite(PRERIS, LOW);
      lcd.setCursor(0, 1);
      lcd.print("extrude         ");
      digitalWrite(ESTRUDE, HIGH);
      stato = 2;
      sendEvent();
      delay(2000);
      digitalWrite(ESTRUDE, LOW);
      lcd.setCursor(0, 1);
      lcd.print("target          ");
      digitalWrite(TARGET, HIGH);
      stato = 3;
      sendEvent();
      delay(2000);
      digitalWrite(TARGET, LOW);
      stato = 0;
      key_flag = 0;
         }
    else if (key_flag == 3) {
      lcd.setCursor(0, 0);
      lcd.print("BUT PLUS wait...");
      lcd.setCursor(0, 1);
      lcd.print("preheating");
      digitalWrite(PRERIS, HIGH);
      stato = 1;
      delay(2000);
      digitalWrite(PRERIS, LOW);
      lcd.setCursor(0, 1);
      lcd.print("extrude         ");
      digitalWrite(ESTRUDE, HIGH);
      stato = 2;
      sendEvent();
      delay(2000);
      digitalWrite(ESTRUDE, LOW);
      lcd.setCursor(0, 1);
      lcd.print("target          ");
      digitalWrite(TARGET, HIGH);
      stato = 3;
      sendEvent();
      delay(2000);
      digitalWrite(TARGET, LOW);
      stato = 0;
      key_flag = 0;
         }
    else if (key_flag == 4) {
      lcd.setCursor(0, 0);
      lcd.print("BUT PLAY wait...");
      lcd.setCursor(0, 1);
      lcd.print("XYZ HOME");
      digitalWrite(MOVXYZ, HIGH);
      delay(1000);
      stato = 0;
      key_flag = 0;
      digitalWrite(MOVXYZ, LOW);
       }
    else if (key_flag == 5) {
      lcd.setCursor(0, 0);
      lcd.print("PRINTER");
      lcd.setCursor(0, 1);
      lcd.print("IN PRINTING");
      digitalWrite(PRINT, HIGH);
      stato = 5;
         }
    else if (key_flag == 6) {
      digitalWrite(PRINT, LOW);
      lcd.setCursor(0, 0);
      lcd.print("PRINTER");
      lcd.setCursor(0, 1);
      lcd.print("IN PAUSE");
      digitalWrite(PAUSE, HIGH);
      stato = 6;
         }
    else if (key_flag == 0) {
      digitalWrite(PAUSE, LOW);
         }
    if (key_flag <= 3){
       lcd.clear();
      lcd.print("READY");
    }
    sendEvent();  
    cambio = false;
  }
  else
  {
    button.tick();
  }
}
