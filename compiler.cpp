// 3.b compiler
//
// g++ -Wall -o compiler compiler.cpp parser.cpp runtime.cpp knop.cpp rgbled.cpp led.cpp -lbcm2835
// ./compiler

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bcm2835.h>
#include "parser.hpp"
#include "runtime.hpp"

using namespace std;

int main(int nArgc, char* aArgv[]) {

  if(nArgc < 2){
    cout << "usage: " << aArgv[0] << " <path to file>" << endl;
		return 0;
	}

  // Initialiseren
  cout << "03.b compiler" << endl << endl;
  bcm2835_init();
  Runtime oRuntime(RPI_BPLUS_GPIO_J8_11, RPI_BPLUS_GPIO_J8_13, RPI_BPLUS_GPIO_J8_15, RPI_BPLUS_GPIO_J8_18, RPI_BPLUS_GPIO_J8_31, 
    RPI_BPLUS_GPIO_J8_37, RPI_BPLUS_GPIO_J8_29, RPI_BPLUS_GPIO_J8_16);

  if(oRuntime.addCommands(aArgv[1])){
    return -1;
  }

  oRuntime.run();

  // Afsluiten
  cout << endl << "Afgesloten :-)" << endl << endl;
  return 0;
};


