#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

enum class LedState {RED, GREEN, AMBER};

bool detectButtonPress() {
    return (PIND & (1 << PIND2));
}

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
    bool couleurChange = false;
    for(;;){
        if (PIND & 0x04) {
            _delay_ms(10);
            if (PIND & 0x04){ 
                if (cpt == 0)
                    PORTD = 0x01;
                if (cpt == 1)
                    PORTD = 0x02;
                couleurChange = true;
            }
        }
        else {
            PORTD = 0x00;
            if(couleurChange) {
                cpt += 1;
                if (cpt == 2)
                    cpt = 0;
                couleurChange = false;
            }
        }
    }
    
}

int main() {
    test_2 ();
}

//{}