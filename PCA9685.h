#ifndef DEF_SERVO_DRIVER
#define DEF_SERVO_DRIVER

class PCA9685
{
  public:
    PCA9685();
    void init(const uint8_t BUS, const uint8_t PCA9685_ADDRESS);
    void set_pwm_freq(float freq_hz);
    void set_pwm(int channel, int on, int off);
    void set_all_pwm(int on, int off);
    ~PCA9685();

  private:
    int i2cHandle;
    int mode1;
    int prescaleval;
    int prescale;
    int oldmode;
    int newmode;
};

#endif
