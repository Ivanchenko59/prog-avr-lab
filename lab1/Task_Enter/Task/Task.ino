void setup() {
  // put your setup code here, to run once:

  for(int i = 2; i <= 4; i++) {
    pinMode(i, OUTPUT);  
  }

  pinMode(8, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(8)) {
    for(int i = 2; i <= 4; i++) {
      PORTD = 0;
      digitalWrite(i, HIGH); 
      delay(100);
    }
  }
  
  else {
      for(int i = 2; i <= 4; i++) {
        PORTD = 0;
      }
  }  
}
