#include <hal.h>

#include <Arduino.h>

Button btnA = Button(PIN_BTN_A); 
Button btnB = Button(PIN_BTN_B); 
Bounce btnOff = Bounce(); 


void hal_setup() {
    pinMode(PIN_BTN_A, INPUT);
    pinMode(PIN_BTN_B, INPUT);
    pinMode(PIN_BTN_OFF, INPUT);

    btnOff.attach(PIN_BTN_OFF);
    btnOff.interval(5);
}

void hal_loop() {
    btnA.loop();
    btnB.loop();
    //btnOff.update();
}