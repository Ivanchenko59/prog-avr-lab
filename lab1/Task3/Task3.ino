void blink_twice(void);

int value = 0, old_value = 0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  value = Serial.read();
  switch (value) {
    case ('0'): 
      digitalWrite(13, LOW);
      break;
    case ('1'): 
      digitalWrite(13, HIGH);
      break;
    case ('2'): 
      blink_twice();
      break; 
  }
  if (value != old_value) {
    Serial.println((char)value);
    old_value = value;
  }
    
}

void blink_twice(void) {
  PORTB = 0;
  for (int i = 0; i < 4; i++) {
    PORTB ^= 1 << 5;
    delay(100);
  }
}

/* Task
 * 1. see function blink_twice
 * 2. see code
 */
