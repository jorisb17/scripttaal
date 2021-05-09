#include "knop.hpp"

Knop::Knop(){
}

Knop::~Knop(){
  
}


/**
  @brief set a GPIO pin on the pi as a button input 
  @param nGPIO The pin to be used as input
  @return void 
* */
void Knop::init(uint8_t nGPIO){
  nPin_ = nGPIO;
  bcm2835_gpio_fsel(nPin_, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(nPin_, BCM2835_GPIO_PUD_UP);
}

/**
  @brief Check if the button is pressed
  @return State of button 
* */
bool Knop::isPressed(){
  return bcm2835_gpio_lev(nPin_) != HIGH;
}