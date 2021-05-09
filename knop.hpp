#ifndef _KNOP_HPP_
#define _KNOP_HPP_

#include <stdint.h>
#include <bcm2835.h>

class Knop {
  public:
    Knop();
    ~Knop();
    void init(uint8_t nGPIO);
    bool isPressed(void);
  private:
    uint8_t nPin_;
};

#endif //_KNOP_HPP_