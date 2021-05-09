#include "runtime.hpp"

/**
 * @brief Initialize all the classes that the runtime uses
 * @param nGPIO_RGB_R The GPIO pin of the red status LED
 * @param nGPIO_RGB_G The GPIO pin of the green status LED
 * @param nGPIO_RGB_B The GPIO pin of the blue status LED
 * @param nGPIO_K The GPIO pin of the button
 * @param nGPIO_LED_Y The GPIO pin of the yellow LED
 * @param nGPIO_LED_R The GPIO pin of the red LED
 * @param nGPIO_LED_G The GPIO pin of the green LED
 * @param nGPIO_LED_B The GPIO pin of the blue LED
 * */
Runtime::Runtime(uint8_t nGPIO_RGB_R, uint8_t nGPIO_RGB_G, uint8_t nGPIO_RGB_B, uint8_t nGPIO_K, uint8_t nGPIO_LED_Y, 
  uint8_t nGPIO_LED_R, uint8_t nGPIO_LED_G, uint8_t nGPIO_LED_B){

  oRGBLed1.init(nGPIO_RGB_R, nGPIO_RGB_G, nGPIO_RGB_B);
  oLedRed.init(nGPIO_LED_R);
  oLedGreen.init(nGPIO_LED_G);
  oLedBlue.init(nGPIO_LED_B);
  oLedYellow.init(nGPIO_LED_Y);

  oKnop1.init(nGPIO_K);

  oRGBLed1.redOn();
  oRGBLed1.greenOn();

  oLedBlue.on();
  oLedRed.on();
  oLedGreen.on();
  oLedYellow.on();

  usleep(2000000);

  oRGBLed1.redOff();

  oLedBlue.off();
  oLedRed.off();
  oLedGreen.off();
  oLedYellow.off();

  nCommandPos_ = 0;
}

Runtime::~Runtime(void){
  oRGBLed1.off();
  oLedBlue.off();
  oLedRed.off();
  oLedGreen.off();
  oLedYellow.off();
}

/**
 * @brief Add commands form a text file to the runtime
 * @param file The path to a text file
 * @return If the commands were added succesfully
 * */
bool Runtime::addCommands(char *file){
  ifstream list(file);
  string str;
  vector<string> line;
  while (getline(list, str))
  {
    try{
      line = oParser.parse(str);
      commands_.push_back(line);
    }catch(invalid_argument& e){
      cerr << e.what() <<endl;
      error();
      return true;
    }
  }
  return false;
}

/**
 * @brief Run all the commands stored in the commands list
 * @return void
 * */
void Runtime::run(void){
  while(nCommandPos_ < commands_.size()){
    vector<string> command = commands_.at(nCommandPos_);
    
    if(command.size() == 4){
      if(command.at(0) == "Jumpknop"){
        cout << "check is button is pressed" << endl;
        jumpKnop(command.at(1), command.at(2), command.at(3));
      }
    }else if(command.size() == 3){
      if(command.at(0) == "Led"){
        cout << "Turning led: " << command.at(1) << " " << command.at(2) << "!" << endl;
        if(command.at(2) == "on"){
          cout << "set " << command.at(1) << " on" << endl;
          led(command.at(1), true);
        }else if(command.at(2) == "off"){
          cout << "set " << command.at(1) << " off" << endl;
          led(command.at(1), false);
        }else{
          cout << "Syntax error: led state can only be on or off" <<endl;
        }
      }
    }else if(command.size() == 2){
      if(command.at(0) == "Wait"){
        int delay = stoi(command.at(1));
        cout << "wait " << delay << " ms" << endl;
        wait(delay);
      }else if(command.at(0) == "Jump"){
        cout << "Jump to label: " << command.at(1) << endl;
        jump(command.at(1));
      }
    }
    cout << endl;
    nCommandPos_++;
  }
}

/**
 * @brief Check if a button is pressed
 * @param sName The name of the button to be checked
 * @return void
 * */
void Runtime::knop(string sName){
  if(sName == "k1"){
    knopK1State_ = oKnop1.isPressed();
  }
}

/** 
 * @brief Set a LED
 * @param sName The name of the LED
 * @param bState The state of the LED
 * @return void
 * */
void Runtime::led(string sName, bool bState){
  if(sName == "red"){
    ledRedState_ = bState; 
    oLedRed.set(ledRedState_);
  }
  if(sName == "green"){
    ledGreenState_ = bState;
    oLedGreen.set(ledGreenState_);
  }
  if(sName == "blue"){
    ledBlueState_ = bState;
    oLedBlue.set(ledBlueState_);
  }
  if(sName == "yellow"){
    ledYellowState_ = bState;
    oLedYellow.set(ledYellowState_);
  }
}

/**
 * @brief Jump to a Label
 * @param sName The name of the label
 * @return void
 * */
void Runtime::jump(string sName){
  for(uint8_t i =0; i < commands_.size(); i++){
    if(commands_.at(i).at(0) == "Label"){
      if(commands_.at(i).at(1) == sName){
        nCommandPos_ = i-1;
        break;
      }
    }
  }
}

/**
 * @brief Jump to a label with a button
 * @param sName the name of the button
 * @param sState The state of the button for when to jump
 * @param sLabel The name of the label to jumpt to
 * @return void
 * */
void Runtime::jumpKnop(string sName, string sState, string sLabel){
  if(sName == "k1"){
    knopK1State_ = oKnop1.isPressed();
    if(sState == "ja"){
      if(knopK1State_){
        jump(sLabel);
      }
    }else if(sState == "nee"){
      if(!knopK1State_){
        jump(sLabel);
      }
    }
  }
}

/**
 * @brief Wait x milliseconds
 * @param nMilliSeconds The ammount of milliseconds to wait
 * @return void
 * */
void Runtime::wait(int nMilliSeconds){
  int microseconds = nMilliSeconds*1000;
  usleep(microseconds);
}

/**
 * @brief Blink to red status LED when there is an error
 * @return void
 * */
void Runtime::error(void){
  oRGBLed1.off();
  int timer = 0;
  bool flag = true;
  while(timer < 30){
    if(flag){
      oRGBLed1.redOn();
      flag = false;
    }else{
      oRGBLed1.redOff();
      flag = true;
    }
    timer++;
    wait(1000);
  }
}
