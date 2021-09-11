#define DELAY_TIME 1000

int count = 0;
unsigned long new_time = 0;
uint8_t flag = 0, old_flag = 0;

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
    flag = 1;
  }
  else {
    digitalWrite(13, LOW);
    flag = 0;
  }

  if (flag != old_flag) {
    (flag) ? Serial.println("Led ON") : Serial.println("Led OFF");
    old_flag = flag;
  }
}

/* Task
 * 1. int has size 4 byte, char 1 byte
 * 2. see code
 */
