#include <Servo.h>

Servo horizontal;
int servoh = 180;
int servohLimitHigh = 175;
int servohLimitLow = 5;

Servo vertical;
int servov = 45;
int servovLimitHigh = 60;
int servovLimitLow = 1;

int ldrlt = A0;
int ldrrt = A3;
int ldrld = A1;
int ldrrd = A2; // Fixed duplicate A3 issue

void setup() {
  horizontal.attach(9);
  vertical.attach(10);
  horizontal.write(servoh);
  vertical.write(servov);
  delay(2500);
}

void loop() {
  int lt = analogRead(ldrlt);
  int rt = analogRead(ldrrt);
  int ld = analogRead(ldrld);
  int rd = analogRead(ldrrd);
  int dtime = 10, tol = 90;

  int avt = (lt + rt) / 2;
  int avd = (ld + rd) / 2;
  int avl = (lt + ld) / 2;
  int avr = (rt + rd) / 2;
  int dvert = avt - avd;
  int dhoriz = avl - avr;

  // Vertical servo movement
  if (-1 * tol > dvert || dvert > tol) {
    if (avt > avd) {
      servov++;
      if (servov > servovLimitHigh) {
        servov = servovLimitHigh;
      }
    } else if (avt < avd) {
      servov--;
      if (servov < servovLimitLow) {
        servov = servovLimitLow;
      }
    }
    vertical.write(servov); // Fixed incorrect variable name
  }

  // Horizontal servo movement
  if (-1 * tol > dhoriz || dhoriz > tol) {
    if (avl > avr) {
      servoh--;
      if (servoh < servohLimitLow) { // Fixed incorrect condition
        servoh = servohLimitLow;
      }
    } else if (avl < avr) {
      servoh++;
      if (servoh > servohLimitHigh) { // Fixed incorrect variable name
        servoh = servohLimitHigh;
      }
    } else if (avl == avr) { // Fixed incorrect comparison operator
      delay(5000);
    }
    horizontal.write(servoh); // Fixed incorrect variable name
  }

  delay(dtime);
}
