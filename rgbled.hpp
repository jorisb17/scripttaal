#ifndef _RGBLED_HPP_
#define _RGBLED_HPP_

#include <stdint.h>
#include <bcm2835.h>

class RGBLed {
  public:
    RGBLed();
    ~RGBLed(void);
    void init(uint8_t nGPIO_R, uint8_t nGPIO_G, uint8_t nGPIO_B);
    void redOn(void);
    void redSet(bool bSate);
    void redOff(void);
    void greenOn(void);
    void greenSet(bool bSate);
    void greenOff(void);
    void blueOn(void);
    void blueSet(bool bSate);
    void blueOff(void);
    void on(void);
    void off(void);
  private:
    uint8_t nPin_R_;
    uint8_t nPin_G_;
    uint8_t nPin_B_;
};

#endif //_RGB_HPP_