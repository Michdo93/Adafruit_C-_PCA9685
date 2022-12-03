# Adafruit_C-_PCA9685
 C++ code to use the PCA9685 PWM servo/LED controller with a Raspberry Pi.

## Installation

To install the library from source (recommended) run the following commands on a Raspberry Pi:

```
sudo apt-get install pigpio
sudo systemctl start pigpiod
sudo systemctl enable pigpiod
cd ~
git clone https://github.com/Michdo93/Adafruit_C-_PCA9685.git
cd Adafruit_C-_PCA9685
g++ -Wall -pthread libPCA9685Sample.cpp PCA9685.cpp -o testServo -lpigpio -lrt
sudo ./testServo
```
