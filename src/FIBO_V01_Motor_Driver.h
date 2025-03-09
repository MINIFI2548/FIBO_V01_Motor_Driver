#include<Arduino.h>
#include "pio_encoder.h"

#ifndef FIBO_V01_MOTOR_DRIVER_H
#define FIBO_V01_MOTOR_DRIVER_H

class Motor{
    private :
        uint8_t ENB, HIGH_PIN, LOW_PIN, ENC_A, ENC_B, HOMING;
        int pulsesPerRevolution = 8192;
        double gearRatio = 1; // encoder / output
       
        PioEncoder encoder;
        int dutycycle;
     public :
        Motor(uint8_t ENB, uint8_t HIGH_PIN, uint8_t LOW_PIN, uint8_t ENCODER_A, uint8_t ENCODER_B, uint8_t HOMING);

        // set & set function
        void begin();
        void info();
        
        bool homed();
        long getEncoder(); // get valuable for motor 
        double getRevolution(); // get revolution of output
        void setGearRatio(double gearRatio);
        void setPPR(int pulsesPerRevolution);
        int getDutycycle();
        // controll function 
        void setDutycycle(int dutycycle);   
        int getPPR();  
};

#endif // FIBO_V01_MOTOR_DRIVER_H