#include "rgbled.hpp"

RGBLed::RGBLed(){
  
}

RGBLed::~RGBLed(){

}

/**
 * @brief Set three GPIO pins for a RGB LED
 * @param nGPIO_R The GPIO pin for the red LED
 * @param nGPIO_G The GPIO pin for the green LED
 * @param nGPIO_B The GPIO pin for the blue LED
 * @return void
 * */
void RGBLed::init(uint8_t nGPIO_R, uint8_t nGPIO_G, uint8_t nGPIO_B){
  nPin_R_ = nGPIO_R;
  nPin_G_ = nGPIO_G;
  nPin_B_ = nGPIO_B;

  bcm2835_gpio_fsel(nPin_R_, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(nPin_G_, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(nPin_B_, BCM2835_GPIO_FSEL_OUTP);
}

/**
 * @brief Set all LEDS on
 * @return void
 * */
void RGBLed::on(){
  bcm2835_gpio_write(nPin_R_, HIGH);
  bcm2835_gpio_write(nPin_G_, HIGH);
  bcm2835_gpio_write(nPin_B_, HIGH);
} 

/**
 * @brief Set all LEDS off
 * @return void
 * */
void RGBLed::off(){
  bcm2835_gpio_write(nPin_R_, LOW);
  bcm2835_gpio_write(nPin_G_, LOW);
  bcm2835_gpio_write(nPin_B_, LOW);
}

/**
 * @brief Set the red LED on
 * @return void
 * */
void RGBLed::redOn(){
  bcm2835_gpio_write(nPin_R_, HIGH);
}

/**
 * @brief Set the red LED on with a variable
 * @param bState The state of the red LED
 * @return void
 * */
void RGBLed::redSet(bool bSate){
  bcm2835_gpio_write(nPin_R_, bSate);
}

/**
 * @brief Set the red LED off
 * @return void
 * */
void RGBLed::redOff(){
  bcm2835_gpio_write(nPin_R_, LOW);
}

/**
 * @brief Set The green LED on
 * @return void
 * */
void RGBLed::greenOn(){
  bcm2835_gpio_write(nPin_G_, HIGH);
}

/**
 * @brief Set the green LED with a variable
 * @param bState The state of the green LED
 * @return void
 * */
void RGBLed::greenSet(bool bSate){
  bcm2835_gpio_write(nPin_G_, bSate);
}

/**
 * @brief Set the green LED off
 * @return void
 * */
void RGBLed::greenOff(){
  bcm2835_gpio_write(nPin_G_, LOW);
}

/**
 * @brief Set the blue LED on
 * @return void
 * */
void RGBLed::blueOn(){
  bcm2835_gpio_write(nPin_B_, HIGH);
}

/**
 * @brief Set the blue LED with a variable
 * @param bState The state of the blue LED
 * @return void
 * */
void RGBLed::blueSet(bool bSate){
  bcm2835_gpio_write(nPin_B_, bSate);
}

/**
 * @brief Set the blue LED off
 * @return void
 * */
void RGBLed::blueOff(){
  bcm2835_gpio_write(nPin_B_, LOW);
}