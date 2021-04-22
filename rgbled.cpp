#include "rgbled.hpp"

RGBLed::RGBLed(){
  
}

RGBLed::~RGBLed(){

}

void RGBLed::init(uint8_t nGPIO_R, uint8_t nGPIO_G, uint8_t nGPIO_B){
  nPin_R_ = nGPIO_R;
  nPin_G_ = nGPIO_G;
  nPin_B_ = nGPIO_B;

  bcm2835_gpio_fsel(nPin_R_, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(nPin_G_, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_fsel(nPin_B_, BCM2835_GPIO_FSEL_OUTP);
}

void RGBLed::on(){
  bcm2835_gpio_write(nPin_R_, HIGH);
  bcm2835_gpio_write(nPin_G_, HIGH);
  bcm2835_gpio_write(nPin_B_, HIGH);
} 

void RGBLed::off(){
  bcm2835_gpio_write(nPin_R_, LOW);
  bcm2835_gpio_write(nPin_G_, LOW);
  bcm2835_gpio_write(nPin_B_, LOW);
}

void RGBLed::redOn(){
  bcm2835_gpio_write(nPin_R_, HIGH);
}

void RGBLed::redSet(bool bSate){
  bcm2835_gpio_write(nPin_R_, bSate);
}

void RGBLed::redOff(){
  bcm2835_gpio_write(nPin_R_, LOW);
}

void RGBLed::greenOn(){
  bcm2835_gpio_write(nPin_G_, HIGH);
}

void RGBLed::greenSet(bool bSate){
  bcm2835_gpio_write(nPin_G_, bSate);
}

void RGBLed::greenOff(){
  bcm2835_gpio_write(nPin_G_, LOW);
}

void RGBLed::blueOn(){
  bcm2835_gpio_write(nPin_B_, HIGH);
}

void RGBLed::blueSet(bool bSate){
  bcm2835_gpio_write(nPin_B_, bSate);
}

void RGBLed::blueOff(){
  bcm2835_gpio_write(nPin_B_, LOW);
}