#include "knop.hpp"

Knop::Knop(){
}

Knop::~Knop(){
  
}

void Knop::init(uint8_t nGPIO){
  nPin_ = nGPIO;
  bcm2835_gpio_fsel(nPin_, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(nPin_, BCM2835_GPIO_PUD_UP);
}

bool Knop::isPressed(){
  return bcm2835_gpio_lev(nPin_) == HIGH;
}