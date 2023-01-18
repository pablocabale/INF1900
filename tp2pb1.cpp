// Tp2 - Pablo Cabale et Abdelnour Sikouky - Equipe 143
// Description ......
// Identifications .......
// Table des etats .......

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#define GREEN_LED_TIME 2000
const uint8_t DEBOUNCE_DELAY = 15;
const uint8_t LIMIT_BUTTON_PUSHES = 2;


enum class LedState {GREEN};

bool detectButtonPress() {
    if (PIND & (1 << PIND2)) {
        _delay_ms(DEBOUNCE_DELAY);
        return (PIND & (1 << PIND2));
    }
    return false;
}

void switchLedGreen() {
    PORTD &= -(1 << PORTD0);
    PORTD |= (1<< PORTD1);
}

void switchLedBlack() {
    PORTD = 0;
}

void changeState(uint8_t& counter){
    switch (counter)
    {
        case LIMIT_BUTTON_PUSHES: 
            counter = 0; 
            switchLedGreen();
            _delay_ms(GREEN_LED_TIME);
            switchLedBlack();
            break;
        default: counter += 1; 
            break;
    }
}

int main() {
    DDRD = 0x03;

    uint8_t count = 0;
    bool pressed = false;
    while(true) {
        if(detectButtonPress())
            pressed = true;
        else if(pressed) {
            changeState(count);
            pressed = false; 
        }
    }
}