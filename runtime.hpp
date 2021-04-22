#ifndef _RUNTIME_HPP_
#define _RUNTIME_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <unistd.h>
#include "knop.hpp"
#include "led.hpp"
#include "rgbled.hpp"

using namespace std;

class Runtime{
  public:
    Runtime(uint8_t nGPIO_R, uint8_t nGPIO_G, uint8_t nGPIO_B, uint8_t nGPIO_K, uint8_t nGPIO_L);
    ~Runtime(void);
    void addCommand(vector<string> vCommand);
    void run(void);
  private:
    void knop(string sName, bool bState);
    void led(string sName, bool bState);
    void jump(string sName);
    void wait(int nMilliSeconds);
    void jumpKnop(string sName, string sState, string sLabel);
    bool ledRedState_;
    bool ledGreenState_;
    bool ledBlueState_;
    bool knopK1State_;
    vector<vector<string>> commands_;
    uint8_t nCommandPos_;
    RGBLed oRGBLed1;
    Led oLed1;
    Knop oKnop1;
};

#endif //_RUNTIME_HPP_