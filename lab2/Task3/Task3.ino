#define DRIVER_ONES   10
#define DRIVER_TENS   11

void  num_to_driver(uint8_t driver, uint8_t digit);
void display_number(uint8_t num);

uint8_t num = 0;
uint32_t new_time = 0;

void setup() {
  for (int i = 1; i <= 13; i++) {
    pinMode(i, OUTPUT);  
  }
  PORTD = 0;
}

void loop() {
    display_number(num);
    if (millis() - new_time > 1000) {
      num = (num + 1) % 60;
      new_time = millis();
    }
}

void display_number(uint8_t num) 
{  
  uint8_t tens = num / 10;
  uint8_t ones = num % 10;

  num_to_driver(1, tens);
  delay(5);
  num_to_driver(0, ones);
  delay(5);
}

void num_to_driver(uint8_t driver, uint8_t digit)
{   
    digitalWrite(DRIVER_TENS, HIGH);
    digitalWrite(DRIVER_ONES, HIGH);
    (driver) ? digitalWrite(DRIVER_TENS, LOW) : digitalWrite(DRIVER_ONES, LOW);
    PORTD = (digit << 2) & (0b1111 << 2);
}
