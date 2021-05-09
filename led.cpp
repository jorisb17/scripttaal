#include "led.hpp"

Led::Led(){
  
}

Led::~Led(){

}


/**
 * @brief initialaze a GPIO pin as a LED
 * @param nGPIO The pin to be set as a LED 
 * @return void
 * */
void Led::init(uint8_t nGPIO){
  nPin_ = nGPIO;
  bcm2835_gpio_fsel(nPin_, BCM2835_GPIO_FSEL_OUTP);
}

/**
 * @brief Turn on the LED
 * @return void
 * */
void Led::on(){
  bState_ = true;
  bcm2835_gpio_write(nPin_, HIGH);
}

/**
 * @brief Turn the LED off
 * @return void
 * */
void Led::off(){
  bState_ = false;
  bcm2835_gpio_write(nPin_, LOW);
}

/**
 * @brief Toggle the LED
 * @return void
 * */
void Led::toggle(){
  bState_ = !bState_;
  bcm2835_gpio_write(nPin_, bState_);
}

/**
 * @brief Set the LED with a variable
 * @param bState The state of the button to be set
 * */
void Led::set(bool bState){
  bState_ = bState;
  bcm2835_gpio_write(nPin_, bState_);
}