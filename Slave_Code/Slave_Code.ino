#include <ezOutput.h>
#include <OneButton.h>
#include <Wire.h>

ezOutput HOME_LED(5);
ezOutput MINUS_LED(4);
ezOutput PLUS_LED(3);
ezOutput PLAY_LED(2);

OneButton HOME_BUT(10, true);
OneButton MINUS_BUT(11, true);
OneButton PLUS_BUT(12, true);
OneButton PLAY_BUT(13, true);

int stato = 0;
int key_flag = 0;
bool cambio = false;

void setup() {
  HOME_BUT.attachClick(homeClick);
  HOME_BUT.attachLongPressStart(homeClick_longPress);
  MINUS_BUT.attachClick(minusClick);
  PLUS_BUT.attachClick(plusClick);
  PLAY_BUT.attachClick(playClick);
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  Serial.println("Welcome to SLAVE");
}

void sendEvent() {
  Wire.beginTransmission(0);
  Wire.write(key_flag);
  Wire.endTransmission();
  Serial.print("sent: ");
  Serial.println(key_flag);
  cambio = true;
}

void receiveEvent(int howMany) {
  stato = Wire.read();
  Serial.print("received: ");
  Serial.println(stato);
  if (stato > 4) {
    key_flag = stato;
  }
  cambio = true;
}

void homeClick() { // key_flag = 1  - Z HOME
  if (key_flag == 2 || key_flag == 3 || key_flag == 4|| key_flag == 5 || key_flag == 6)
    return;
  stato = 1;
  key_flag = 1;

  sendEvent();
}
void homeClick_longPress() {
  if (key_flag == 1 || key_flag == 2 || key_flag == 3|| key_flag == 5 || key_flag == 6)
    return;
  stato = 1;
  key_flag = 4;
  sendEvent();
} // longPressStart1

void minusClick() { // key_flag == 2
  if (key_flag == 1 || key_flag == 3 || key_flag == 4|| key_flag == 5 || key_flag == 6)
    return;
  stato = 1;
  key_flag = 2;
  sendEvent();
}

void plusClick() { // key_flag == 3
  if (key_flag == 1 || key_flag == 2 || key_flag == 4|| key_flag == 5 || key_flag == 6)
    return;
  stato = 1;
  key_flag = 3;
  sendEvent();
}

void playClick() { // key_flag == 4
  if (key_flag == 1 || key_flag == 2 || key_flag == 3|| key_flag == 5 || key_flag == 6)
    return;
  stato = 1;
  key_flag = 4;
  sendEvent();
}

void loop() {


  if (stato == 0) {
    key_flag = 0;
    HOME_LED.low();
    MINUS_LED.low();
    PLUS_LED.low();
    PLAY_LED.low();
    cambio == false;
  }

  if (cambio == true) {




    switch (key_flag) {
      case 1: // home
        key_flag == 1;
        HOME_LED.blink(200, 200);
        HOME_LED.loop();
        break;
      case 2: // minus
        key_flag == 2;
        switch (stato) {
          case 1:
            stato == 1;
            MINUS_LED.blink(100, 100);
            break;
            stato == 2;
            MINUS_LED.blink(200, 200);
            break;
            stato == 3;
            MINUS_LED.blink(300, 300);
            break;
          default:
            break;
        }
        MINUS_LED.loop();
        break;
      case 3: // plus
        key_flag == 3;
        switch (stato) {
          case 1:
            stato == 1;
            PLUS_LED.blink(100, 100);
            break;
            stato == 2;
            PLUS_LED.blink(200, 200);
            break;
            stato == 3;
            PLUS_LED.blink(300, 300);
            break;
          default:
            break;
        }
        PLUS_LED.loop();
        break;
      case 4:
        key_flag == 4;
        PLAY_LED.blink(200, 200);
        PLAY_LED.loop();
        break;
      case 5: // PRINTING
        key_flag == 5;
        PLAY_LED.blink(200, 200);
        PLAY_LED.loop();
        break;
      case 6: // PAUSE
        key_flag == 6;
        PLAY_LED.blink(300, 300);
        PLAY_LED.loop();
        break;

      default:
        cambio = false;
        break;
    }

  }
  else {
    HOME_BUT.tick();
    MINUS_BUT.tick();
    PLUS_BUT.tick();
    PLAY_BUT.tick();
  }
}
