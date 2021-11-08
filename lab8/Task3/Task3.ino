
int main(void)
{
    DDRB |= (1 << PB5) | (1 << PB1);
    DDRB &= ~((1 << PB4) | (1 << PB0));
    PORTB |= (1 << PB4) | (1 << PB0);
    
    DDRC |= (1 << PC1) | (1 << PC5);
    DDRC &= ~((1 << PC0) | (1 << PC4)) ;
    PORTC |= (1 << PC0) | (1 << PC4);

    DDRD |= (1 << PD7);
    DDRD &= ~(1 << PD6);
    PORTD |= (1 << PD6);


    while(1) {
        !(PINB & (1 << PB4)) ? PORTB |= (1 << PB5) : PORTB &= ~(1 << PB5);
        !(PINB & (1 << PB0)) ? PORTB |= (1 << PB1) : PORTB &= ~(1 << PB1);
        !(PINC & (1 << PC0)) ? PORTC |= (1 << PC1) : PORTC &= ~(1 << PC1);
        !(PINC & (1 << PC4)) ? PORTC |= (1 << PC5) : PORTC &= ~(1 << PC5);
        !(PIND & (1 << PD6)) ? PORTD |= (1 << PD7) : PORTD &= ~(1 << PD7);
    }
}
