#include "runtime.hpp"

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

  usleep(5000000);

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

void Runtime::run(void){
  while(nCommandPos_ < commands_.size()){
    vector<string> command = commands_.at(nCommandPos_);
    
    if(command.size() == 4){
      if(command.at(0).compare("Jumpknop") == 0){
        cout << "check is button is pressed" << endl;
        jumpKnop(command.at(1), command.at(2), command.at(3));
      }
    }else if(command.size() == 3){
      if(command.at(0).compare("Led") == 0){
        cout << "Turning led: " << command.at(1) << " " << command.at(2) << "!" << endl;
        if(command.at(2).compare("on") == 0){
          cout << "set " << command.at(1) << " on" << endl;
          led(command.at(1), true);
        }else if(command.at(2).compare("off") == 0){
          cout << "set " << command.at(1) << " off" << endl;
          led(command.at(1), false);
        }else{
          cout << "Syntax error: led state can only be on or off" <<endl;
        }
      }
    }else if(command.size() == 2){
      if(command.at(0).compare("Wait") == 0){
        int delay = stoi(command.at(1));
        cout << "wait " << delay << " ms" << endl;
        wait(delay);
      }else if(command.at(0).compare("Jump") == 0){
        cout << "Jump to label: " << command.at(1) << endl;
        jump(command.at(1));
      }
    }
    cout << endl;
    nCommandPos_++;
  }
}

void Runtime::knop(string sName, bool bState){
  if(sName.compare("k1")){
    knopK1State_ = oKnop1.isPressed();
  }
}

void Runtime::led(string sName, bool bState){
  if(sName.compare("red") == 0){
    ledRedState_ = bState; 
    oLedRed.set(ledRedState_);
  }
  if(sName.compare("green") == 0){
    ledGreenState_ = bState;
    oLedGreen.set(ledGreenState_);
  }
  if(sName.compare("blue") == 0){
    ledBlueState_ = bState;
    oLedBlue.set(ledBlueState_);
  }
  if(sName.compare("yellow") == 0){
    ledYellowState_ = bState;
    oLedYellow.set(ledYellowState_);
  }
}
  
void Runtime::jump(string sName){
  for(uint8_t i =0; i < commands_.size(); i++){
    if(commands_.at(i).at(0).compare("Label") == 0){
      if(commands_.at(i).at(1).compare(sName) == 0){
        nCommandPos_ = i-1;
        break;
      }
    }
  }
}

void Runtime::jumpKnop(string sName, string sState, string sLabel){
  if(sName.compare("k1") == 0){
    if(sState.compare("ja")){
      if(oKnop1.isPressed()){
        jump(sLabel);
      }
    }else if(sState.compare("nee")){
      if(!oKnop1.isPressed()){
        jump(sLabel);
      }
    }
  }
}

void Runtime::wait(int nMilliSeconds){
  int microseconds = nMilliSeconds*1000;
  usleep(microseconds);
}

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
