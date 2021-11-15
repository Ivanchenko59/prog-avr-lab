int main(void) 
{
    DDRB |= (1 << 5);
    DDRD &= ~(1 << 2);
    PORTD &= ~(1 << 2);

    //Change
    //EICRA |= (1 << 0);
    
    //Falling
//    EICRA |= (1 << 1);
//    EICRA &= ~(1 << 0);

    // Rising
    EICRA |= ((1 << 0) | (1 << 1));
    
    EIMSK = (1 << 0); // INT1=1(off), INT0=1(on)
    sei();
    Serial.begin(9600);
    while(1) {
        
    }
}

ISR(INT0_vect) {
    Serial.println("Interrupt now");
    PORTB ^= (1 << 5);
}
