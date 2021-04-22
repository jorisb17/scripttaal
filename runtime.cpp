#include "runtime.hpp"

Runtime::Runtime(uint8_t nGPIO_R, uint8_t nGPIO_G, uint8_t nGPIO_B, uint8_t nGPIO_K, uint8_t nGPIO_L){
  oRGBLed1.init(nGPIO_R, nGPIO_G, nGPIO_B);
  oLed1.init(nGPIO_L);
  oKnop1.init(nGPIO_K);

  oRGBLed1.off();
  oLed1.off();

  nCommandPos_ = 0;
}

Runtime::~Runtime(void){
  oRGBLed1.off();
  oLed1.off();
}

void Runtime::addCommand(vector<string> vCommand){
  commands_.push_back(vCommand);
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
    oRGBLed1.redSet(ledRedState_);
  }
  if(sName.compare("green") == 0){
    ledGreenState_ = bState;
    oRGBLed1.greenSet(ledGreenState_);
  }
  if(sName.compare("blue") == 0){
    ledBlueState_ = bState;
    oRGBLed1.blueSet(ledBlueState_);
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

