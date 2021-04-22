#include "led.hpp"

Led::Led(){
  
}

Led::~Led(){

}

void Led::init(uint8_t nGPIO){
  nPin_ = nGPIO;
  bcm2835_gpio_fsel(nPin_, BCM2835_GPIO_FSEL_OUTP);
}

void Led::on(){
  bState_ = true;
  bcm2835_gpio_write(nPin_, HIGH);
}

void Led::off(){
  bState_ = false;
  bcm2835_gpio_write(nPin_, LOW);
}

void Led::toggle(){
  bState_ = !bState_;
  bcm2835_gpio_write(nPin_, bState_);
}

void Led::set(bool bState){
  bState_ = bState;
  bcm2835_gpio_write(nPin_, bState_);
}