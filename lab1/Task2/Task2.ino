#define DELAY_TIME 1000

int count = 0, new_time = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(millis() - new_time > DELAY_TIME) {
    count++;
    new_time = millis();
  }
  
  if (!(count % 2)) {
    digitalWrite(13, HIGH);
    Serial.println("Led ON");
  }
  else {
    digitalWrite(13, LOW);
    Serial.println("Led OFF");
  }
}

/* Task
 * 1. int has size 4 byte, char 1 byte
 * 2. see code
 */
