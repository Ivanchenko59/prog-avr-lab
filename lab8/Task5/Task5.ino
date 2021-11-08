const byte helloSegments[] = {
    0x76, // H
    0x79, // E
    0x38, // L
    0x38, // L
    0x5C, // o
    0x00  // нічого
};
int len = sizeof(helloSegments);
const uint32_t myDelay = 300;
bool stateButton_pin12(void) 
{
    int buttonState = PINB & (1 << PB4);
    return buttonState == 0 ? true : false;
}

bool stateButton_pin13(void)
{
    int buttonState = PINB & (1 << PB5);
    return buttonState == 0 ? true : false;
}

void myF(int i, int &num, bool state)
{
    PORTB = B001111; // встановлюємо високий рівень на пінах 8-11 порта В
    if (state) {
        if (num == 3) PORTB &= B001110 & B001111;
        if (num == 2) PORTB &= B001101 & B001111;
        if (num == 1) PORTB &= B001011 & B001111;
        if (num == 0) PORTB &= B000111 & B001111;
    }
    else {
        if (num == 0) PORTB &= B001110 & B001111;
        if (num == 1) PORTB &= B001101 & B001111;
        if (num == 2) PORTB &= B001011 & B001111;
        if (num == 3) PORTB &= B000111 & B001111;
    }
    
    int index;
    if (i - num >= 0) index = i - num;
    else index = len - 1;
    if (index >= len) index = len - 1;
    
    PORTD = helloSegments[index];
    if (stateButton_pin12()) PORTD |= 1 << PD7;
    else PORTD &= ~(1 << PD7);
    delay(1);
    num = (num + 1) % 4;
}

void setup() {
  DDRD = B11111111; // піни пора D (на платі 0-7 піни) як виходи
  DDRB = B001111; // піни порта B (на платі 8-11 піни) позначаєм вихідними
  PORTB = B001111; // встановлюємо високий рівень пінів порта В (на платі 8-11 піни)
  
  DDRB &= ~((1 << PB4) | (1 << PB5));
  PORTB |= (1 << PB4) | (1 << PB5);// 12 і 13 позначаєм вхідними (4 і 5 піни регістра B)
}

void loop() {
    for (int i = 0; i < len + 4; i++) {
        int num = 0;
        uint32_t myTime = millis();
        delay(1);
        while (millis() - myTime < myDelay) {
            bool state13 = stateButton_pin13();
            myF(i, num, state13);
        }
    }
}
