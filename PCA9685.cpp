#include <iostream>
#include <stdio.h>
#include <pigpio.h>
#include <cstdint>
#include <cstdarg>
#include <chrono>
#include <cmath>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "PCA9685.h"

// Registers/etc:
//#define PCA9685_ADDRESS 0x40
#define MODE1 0x00
#define MODE2 0x01
#define SUBADR1 0x02
#define SUBADR2 0x03
#define SUBADR3 0x04
#define PRESCALE 0xFE
#define LED0_ON_L 0x06
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define ALL_LED_ON_L 0xFA
#define ALL_LED_ON_H 0xFB
#define ALL_LED_OFF_L 0xFC
#define ALL_LED_OFF_H 0xFD

// Bits:
#define RESTART 0x80
#define SLEEP 0x10
#define ALLCALL 0x01
#define INVRT 0x10
#define OUTDRV 0x04

/*PCA9685 PWM LED/servo controller.*/
PCA9685::PCA9685(){}

/*Initialize the PCA9685.*/
void PCA9685::init(const uint8_t BUS, const uint8_t PCA9685_ADDRESS)
{
    i2cHandle = i2cOpen(BUS, PCA9685_ADDRESS, 0);

    setAllPWM(0, 0);

    i2cWriteByteData(i2cHandle, MODE2, OUTDRV);
    i2cWriteByteData(i2cHandle, MODE1, ALLCALL);

    usleep(5000);  // wait for oscillator
    int mode1 = (i2cReadByteData(i2cHandle, MODE1)) + 128;  // unsigned byte to byte conversion

    mode1 = mode1 & (~SLEEP);  // wake up (reset sleep)

    i2cWriteByteData(i2cHandle, MODE1, mode1);
    usleep(5000);  // wait for oscillator
}

/*Set the PWM frequency to the provided value in hertz.*/
void PCA9685::setPWMFreq(const float *freq_hz)
{
    int preScaleVal = (int)(25000000.0f / (4096 * freq_hz) - 1.0f);

    int preScale = (int)floor(preScaleVal + 0.5);

    int oldMode = (i2cReadByteData(i2cHandle, MODE1)) + 128;  // unsigned byte to byte conversion
    int newMode = (oldMode & 0x7F) | 0x10;    // sleep

    i2cWriteByteData(i2cHandle, MODE1, newMode);  // go to sleep
    i2cWriteByteData(i2cHandle, PRESCALE, preScale);
    i2cWriteByteData(i2cHandle, MODE1, oldMode);

    usleep(5000);

    i2cWriteByteData(i2cHandle, MODE1, oldMode | 0x80);
}

/*Sets a single PWM channel.*/
void PCA9685::setPWM(int channel, int on, int off)
{
    i2cWriteByteData(i2cHandle, LED0_ON_L+4*channel, on & 0xFF);
    i2cWriteByteData(i2cHandle, LED0_ON_H+4*channel, on >> 8);
    i2cWriteByteData(i2cHandle, LED0_OFF_L+4*channel, off & 0xFF);
    i2cWriteByteData(i2cHandle, LED0_OFF_H+4*channel, off >> 8);
}

/*Sets all PWM channels.*/
void PCA9685::setAllPWM(int on, int off)
{
    i2cWriteByteData(i2cHandle, ALL_LED_ON_L, on & 0xFF);
    i2cWriteByteData(i2cHandle, ALL_LED_ON_H, on >> 8);
    i2cWriteByteData(i2cHandle, ALL_LED_OFF_L, off & 0xFF);
    i2cWriteByteData(i2cHandle, ALL_LED_OFF_H, off >> 8);
}

PCA9685::~PCA9685()
{
    i2cClose(i2cHandle);
}
