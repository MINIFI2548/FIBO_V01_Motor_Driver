#include"FIBO_V01_Motor_Driver.h"
#include <pio_encoder.h>

// set up
Motor :: Motor(uint8_t ENB, uint8_t HIGH_PIN, uint8_t LOW_PIN, uint8_t ENCODER_A, uint8_t ENCODER_B, uint8_t HOMING) 
    : encoder(ENCODER_A), ENB(ENB), HIGH_PIN(HIGH_PIN), LOW_PIN(LOW_PIN), HOMING(HOMING){
}   

void Motor :: info() { 
    Serial.print("ENB PIN -> ");
    Serial.print(ENB);
    Serial.print(" | HIGHT PIN -> ");
    Serial.print(HIGH_PIN);
    Serial.print(" | LOW PIN -> ");
    Serial.println(LOW_PIN);
    Serial.print("EncoderA -> ");
    Serial.print(ENC_A);
    Serial.print(" | EncoderB -> ");
    Serial.println(ENC_B);
    Serial.print("Pulses Per Revolution -> ");
    Serial.println(pulsesPerRevolution);
    Serial.print("Ratio between Encoder & Output -> ");
    Serial.println(gearRatio);
}

void Motor :: begin() {
    pinMode(ENB, OUTPUT);
    pinMode(HIGH_PIN, OUTPUT);
    pinMode(LOW_PIN, OUTPUT);
    pinMode(HOMING, INPUT_PULLUP);
    encoder.begin();
    // pinMode(ENC_A, INPUT_PULLUP);
    // pinMode(ENC_B, INPUT_PULLUP);
}

void Motor :: setDutycycle(int dutycycle) {
    dutycycle = min(max(-225, dutycycle), 225);
    if(dutycycle > 0){ 
        digitalWrite(ENB, LOW);
        analogWrite(HIGH_PIN, dutycycle);
        analogWrite(LOW_PIN, 0);
    } 
    else if(dutycycle < 0){ 
        digitalWrite(ENB, LOW);
        analogWrite(HIGH_PIN, 0);
        analogWrite(LOW_PIN, abs(dutycycle));
    }else{
        digitalWrite(ENB, HIGH);
        digitalWrite(HIGH_PIN, LOW);
        digitalWrite(LOW_PIN, LOW);
    }
    this->dutycycle=dutycycle;

}
void Motor :: setGearRatio(double gearRatio){
    this -> gearRatio = gearRatio;
}
void Motor :: setPPR(int pulsesPerRevolution){
    this -> pulsesPerRevolution = pulsesPerRevolution;
}

bool Motor :: homed(){
    return digitalRead(HOMING);
}
long Motor :: getEncoder(){ 
    return encoder.getCount();
}
double Motor :: getRevolution(){
    return double(encoder.getCount()) / double(pulsesPerRevolution) * gearRatio;
}

int Motor ::getDutycycle(){
    return dutycycle;
}

int Motor :: getPPR(){
    return pulsesPerRevolution;
}