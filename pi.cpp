#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void test_1 () {
    DDRC = 0x03;

    for(;;){
        PORTC = 0x01;
        _delay_ms(1000);
        PORTC = 0x02;
        _delay_ms(1000);
        for(int i=0; i < 50; i++){
            PORTC = 0x01;
            _delay_ms(10);
            PORTC = 0x02;
            _delay_ms(10);
        }
    }
}

void test_2 () {
    DDRD = 0x03;

    int cpt = 0;
    for(;;){
        if (PIND & 0x04) {
            _delay_ms(10);
            if (PIND & 0x04){ 
                if (cpt == 0) {
                    PORTD = 0x01;
                }
                if (cpt == 1) {
                    PORTD = 0x02;
                } 
            }
        }
        else {
            PORTD = 0x00;
            cpt += 1;
            if (cpt == 2) {
                cpt = 0;
            } 
        }
    }
    
}

int main() {
    test_2 ();
}

//{}