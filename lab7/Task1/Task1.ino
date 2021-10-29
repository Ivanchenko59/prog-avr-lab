byte helloSegments[] = {
  0x76, // H
  0x79, // E
  0x38, // L
  0x38, // L
  0x5C, // o
  0x00,
  0x00,
  0x00,
  0x00  // нічого
};
byte numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int len = sizeof(helloSegments);
unsigned long myDelay = 200;
int num_of_digit = 1;
int counter = 0;

void myF(int i, int *num)
{
  PORTB |= ~PORTB; //PORTB = B111111; // встановлюємо високий рівень на пінах 8-13 порта В
  PORTB &= ~(1 << *num); // встановлюємо низький рівень піна порта В

  int index = 0;
  if (i - *num >= 0) index = i - *num;
  else index = len - 1;
  if (index >= len) index = len - 1;

 
  PORTD = helloSegments[index];
  delay(1);
  *num = (*num + 1) % 4;
}

void setup() {
    DDRD = B11111111; // піни порту D (на платі 0-7 піни) позначаєм вихідними
    DDRB = B111111; // піни порту B (на платі 8-13 піни) позначаєм вихідними
    PORTB = B111111; // встановлюємо високий рівень пінів порта В (на платі 8-13 піни)

    DDRB |= (1 << PB5);
    DDRB &= ~(1 << PB4);
    PORTB |= (1 << PB4);
}

void loop() {

    helloSegments[5 - 1 + num_of_digit] = numbers[counter % 10];
    if (counter > 9) {
        num_of_digit = 2;
        helloSegments[5] = numbers[counter / 10 % 10];
    }
    if (counter > 99) {
        num_of_digit = 3;
        helloSegments[4] = numbers[counter / 100 % 10];
    }

    helloSegments[5 - 1 + num_of_digit] = numbers[counter % 10];
    
    for (int i = 0; i < len - 4 + num_of_digit + 4; i++) {
        !(PINB & (1 << PB4)) ? myDelay = 50 : myDelay = 250;
        int num = 0;
        long myTime = millis();
        delay(1);
        while (millis() - myTime < myDelay) {
            myF(i, &num);
        }
    }
    counter++;
}
