#ifndef _LED_HPP_
#define _LED_HPP_

#include <stdint.h>
#include <bcm2835.h>

class Led {
  public:
    Led();
    ~Led();
    void init(uint8_t nGPIO);
    void on();
		void off();
    void toggle();
    void set(bool bState);
  private:
    uint8_t nPin_;
    bool bState_ = false;
};

#endif // _LED_HPP_