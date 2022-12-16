#ifndef DEF_SERVO_DRIVER
#define DEF_SERVO_DRIVER

class PCA9685
{
  public:
    PCA9685();
    void init(const uint8_t &BUS, const uint8_t &PCA9685_ADDRESS);
    void setPWMFreq(const float &freq_hz);
    void setPWM(const uint8_t &channel, const uint16_t &on, const uint16_t &off);
    void setAllPWM(const uint16_t &on, const uint16_t &off);
    ~PCA9685();

  private:
    int i2cHandle;
    uint8_t mode1;
    uint16_t preScaleVal;
    uint16_t preScale;
    uint16_t oldMode;
    uint16_t newMode;
};

#endif
