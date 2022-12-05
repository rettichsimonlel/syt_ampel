#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect) {
    PORTB &= ~_BV(PB0);
    PORTB &= ~_BV(PB2);
    PORTB &= ~_BV(PB5);
    PORTB |= _BV(PB3);
    PORTB |= _BV(PB4);
    _delay_ms(2000);
    PORTB &= ~_BV(PB4);
    PORTB |= _BV(PB5);
}

/**
 * @brief Enable interrupts
 * 
 */
void init_interrupt() {
    sei(); // set interrupt bit
    GIMSK = 0b01000000; // INT0 on
    MCUCR = MCUCR | 0b00000001;
    cli(); // clear interrupt bit
}

int main() {
    DDRB = 0b00111111;
    init_interrupt();
    while (1) {

//      Green

        PORTB |= _BV(PB0);
        PORTB &= ~_BV(PB2);
        PORTB &= ~_BV(PB3);
        _delay_ms(2000);

//      Blink Green 4 times

        for (int i = 0; i < 4; i++) {
            _delay_ms(300);
            PORTB &= ~_BV(PB0);
            _delay_ms(300);
            PORTB |= _BV(PB0);
        }
        _delay_ms(300);

//      Yellow

        PORTB &= ~_BV(PB0);
        PORTB |= _BV(PB2);
        PORTB &= ~_BV(PB3);
        _delay_ms(1000);

//      Red

        PORTB &= ~_BV(PB0);
        PORTB &= ~_BV(PB2);
        PORTB |= _BV(PB3);
        _delay_ms(2000);

//      Yellow

        PORTB &= ~_BV(PB0);
        PORTB |= _BV(PB2);
        PORTB &= ~_BV(PB3);
        _delay_ms(1000);
    }
    return 0;
}
