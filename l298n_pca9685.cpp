#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include "PCA9685.h"

using namespace std;

//const uint8_t ENA = 20; // Pin 38   // enableMotor Pin
//const uint8_t IN1 = 6; // Pin 31    // forwardPin
//const uint8_t IN2 = 13; // Pin 33   // backwardPin

const uint16_t dutyCycle = 4095;     // ]0, 4095[
PCA9685 servoDriver;

void init() {
    //PCA9685 servoDriver;
    servoDriver.init(1, 0x40);

    servoDriver.setPWMFreq(100);

    servoDriver.setPWM(4, 0, 0);    // ENA
    servoDriver.setPWM(5, 0, 0);    // IN1
    servoDriver.setPWM(6, 0, 0);    // IN2
}

void setMotorMode(const string &mode) {
    if(mode == "forward") {
        servoDriver.setPWM(5, 0, dutyCycle);            // LOW
        servoDriver.setPWM(6, 0, 0);    // HIGH
    } else if(mode == "reverse") {
        servoDriver.setPWM(5, 0, 0);
        servoDriver.setPWM(6, 0, dutyCycle);
    } else {
        servoDriver.setPWM(5, 0, 0);
        servoDriver.setPWM(6, 0, 0);
    }
}

void setMotor(const double &power) {
    uint16_t pwm;
    if(power > 0) {
        setMotorMode("forward");
        pwm = (int)(dutyCycle * power);
    } else if(power < 0) {
        setMotorMode("reverse");
        pwm = -(int)(dutyCycle * power);
    } else {
        setMotorMode("stopp");
        pwm = 0;
    }

    if (pwm > dutyCycle) {
        pwm = dutyCycle;
    }

    servoDriver.setPWM(4, 0, pwm);
}

int main()
{
    if (gpioInitialise() == -1)
        return -1;

    init();

    printf("Driving forward:\n");
    double speed;
    for (int i = 0; i < 10; i++) {
        speed = 0.1 * i;
        printf("set speed to %f \n", speed);
        setMotor(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    setMotor(speed);

    usleep(3000000);

    printf("Driving reverse:\n");
    for (int i = 0; i < 10; i++) {
        speed = -0.1 * i;
        printf("set speed to %f \n", speed);
        setMotor(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    setMotor(speed);
}
