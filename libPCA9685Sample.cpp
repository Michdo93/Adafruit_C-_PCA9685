#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include "PCA9685.h"

using namespace std;

int main()
{
    if (gpioInitialise() == -1)
        return -1;

    // Initialise the PCA9685 using the default address (0x40).
    PCA9685 pwm;
    pwm.init(1, 0x40);

    int servo_min = 150;    // Min pulse length out of 4096
    int servo_max = 600;    // Max pulse length out of 4096

    // Set frequency to 60hz, good for servos.
    pwm.set_pwm_freq(60);

    while(1) {
        pwm.set_pwm(0, 0, servo_min);
        usleep(1000000);
        pwm.set_pwm(0, 0, servo_max);
        usleep(1000000);
    }
}
