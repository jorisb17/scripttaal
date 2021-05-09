#ifndef _RUNTIME_HPP_
#define _RUNTIME_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <unistd.h>
#include "knop.hpp"
#include "led.hpp"
#include "rgbled.hpp"
#include "parser.hpp"

using namespace std;

class Runtime{
  public:
    Runtime(uint8_t nGPIO_RGB_R, uint8_t nGPIO_RGB_G, uint8_t nGPIO_RGB_B, uint8_t nGPIO_K, uint8_t nGPIO_LED_Y, 
    uint8_t nGPIO_LED_R, uint8_t nGPIO_LED_G, uint8_t nGPIO_LED_B);
    ~Runtime(void);
    bool addCommands(char *file);
    void run(void);
  private:
    void knop(string sName);
    void led(string sName, bool bState);
    void jump(string sName);
    void wait(int nMilliSeconds);
    void jumpKnop(string sName, string sState, string sLabel);
    void error(void);
    bool ledRedState_;
    bool ledGreenState_;
    bool ledBlueState_;
    bool ledYellowState_;
    bool knopK1State_;
    vector<vector<string>> commands_;
    uint8_t nCommandPos_;
    RGBLed oRGBLed1;
    Led oLedRed;
    Led oLedGreen;
    Led oLedBlue;
    Led oLedYellow;
    Knop oKnop1;
    Parser oParser;
};

#endif //_RUNTIME_HPP_