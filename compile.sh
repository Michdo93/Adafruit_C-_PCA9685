#!/bin/bash
g++ -Wall -pthread libPCA9685Sample.cpp PCA9685.cpp -o testServo -lpigpio -lrt
sudo ./testServo
