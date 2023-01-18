#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

//#define DEBOUNCE_DELAY 15
const uint8_t DEBOUNCE_DELAY = 15;
const uint8_t AMBER_DELAY_RED = 5;
const uint8_t AMBER_DELAY_GREEN = 5;

enum class LedState {RED, GREEN, AMBER};

bool detectButtonPress() {
    if (PIND & (1 << PIND2)) {
        _delay_ms(DEBOUNCE_DELAY);
        return (PIND & (1 << PIND2));
    }
    return false;
}

void switchLedRed() {
    PORTA &= -(1 << PORTA1);
    PORTA |= (1<< PORTA0);
}

void switchLedGreen() {
    PORTA &= -(1 << PORTA0);
    PORTA |= (1<< PORTA1);
}

void switchLedAmber() {
    switchLedRed();
    _delay_ms(AMBER_DELAY_RED);
    switchLedGreen();
    _delay_ms(AMBER_DELAY_GREEN);
}

void changeState(LedState& currentState){
    switch (currentState)
    {
        case LedState::RED: currentState = LedState::GREEN; break;
        case LedState::GREEN: currentState = LedState::AMBER; break;
        case LedState::AMBER: currentState = LedState::RED; break;
    }
}

void excecuteStateOutput(LedState& currentState){
    switch (currentState)
    {
        case LedState::RED: switchLedRed(); break;
        case LedState::GREEN: switchLedGreen(); break;
        case LedState::AMBER: switchLedAmber(); break;
    }
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
        if (detectButtonPress()) {
            if (cpt == 0)
                PORTD = 0x01;
            if (cpt == 1)
                PORTD = 0x02;
            couleurChange = true;
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

void test_2_correction () {
    DDRA != (1 << DDA0) | (1 << DDA1);
    LedState currentState = LedState::RED;

    while(true) {
        excecuteStateOutput(currentState);
        if(detectButtonPress()) {
            while(detectButtonPress()) {
                excecuteStateOutput(currentState);
            }
            changeState(currentState);
        }
    }
}

int main() {
    test_2();
}

//{}