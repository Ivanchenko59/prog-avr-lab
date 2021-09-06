#include "SoftwareSerial.h"

SoftwareSerial mySerial(4, 5);
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = mySerial.read();
  if (val == '1') {
    digitalWrite(11, HIGH);
  }
  else if (val == '0') {
    digitalWrite(11, LOW);
  }
}

/** Task
 * 1. done
 * 2. done
 * 3. done
 */
