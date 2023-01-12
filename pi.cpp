#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRC = 0x03;

    for(;;){
        PORTC = 0x01;
        _delay_ms(2000);
        PORTC = 0x02;
        _delay_ms(2000);
    }
}