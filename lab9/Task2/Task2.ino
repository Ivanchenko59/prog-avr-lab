int main(void) 
{
    DDRB |= (1 << 5);
    DDRD &= ~(1 << 2);
    PORTD &= ~(1 << 2);

     //need to config all GPIO but.. :)
    
    PCMSK0 = B00011111; //d8 - d12
    PCMSK1 = B00111111; //a0 - a5
    PCMSK2 = B11111100; //d02 - d7
   
    PCIFR = 0; // clear all interrupt flags
    PCICR = 7; // enable PCIE1 group
    sei();
    Serial.begin(9600);
    while(1) {
        
    }
}

ISR(INT0_vect) 
{
    PORTB ^= (1 << 5);
    Serial.println("Interrupt now");
}

ISR(PCINT1_vect) 
{
    PORTB ^= (1 << 5);
    Serial.println("Interrupt now");
}

ISR(PCINT2_vect)
{
    PORTB ^= (1 << 5);
    Serial.println("Interrupt now");
}
