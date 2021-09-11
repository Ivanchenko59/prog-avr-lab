#define DELAY_TIME 100

int count = 0;
unsigned int new_time = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(count);
  
  if(millis() - new_time > DELAY_TIME) {
    count++;
    new_time = millis();
  }
  if (digitalRead(7)) {
    count = 0;
  }
  
  if (!(count % 2)) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}

/**
 * 1. 2^16 - 1 / 2 = 32767
 * 2. 32767
 * 3. overflow and upcount from -32768 to 32767
 * 4. see code
 * 5. see code
 */
