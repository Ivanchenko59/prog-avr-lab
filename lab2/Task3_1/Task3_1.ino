#define DRIVER_ONES   8
#define DRIVER_TENS   9

void  num_to_driver(uint8_t driver, uint8_t digit);
void display_number(uint8_t num);

uint8_t num = 0;
uint32_t new_time = 0;

uint8_t digitsToSegment[10] =
{
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F,
};


void setup() {
  // put your setup code here, to run once:
  for (int i = 8; i < 11; i++) {
    pinMode(i, OUTPUT);  
  }

  for (int i = 0; i <= 6; i++) {
    pinMode(i, OUTPUT);  
  }
  
}

//8 black, 9 red, 10 brown, black-right 12

void loop() {
  // put your main code here, to run repeatedly:

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
    PORTD = digitsToSegment[digit];
}
