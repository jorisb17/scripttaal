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

#define MAX_INVOER 100

void tokenize(string &str, char delim, vector<string> &out);

int main(int nArgc, char* aArgv[]) {

  if(nArgc < 2){
		printf("usage: %s  <path to file>\n", aArgv[0]);
		return 0;
	}

  // Initialiseren
  printf("03.b compiler\n\n");
  bcm2835_init();
  Runtime oRuntime(RPI_BPLUS_GPIO_J8_11, RPI_BPLUS_GPIO_J8_13, RPI_BPLUS_GPIO_J8_15, RPI_BPLUS_GPIO_J8_18, RPI_BPLUS_GPIO_J8_31, 
    RPI_BPLUS_GPIO_J8_37, RPI_BPLUS_GPIO_J8_29, RPI_BPLUS_GPIO_J8_16);
  
  vector<vector<string>> commands;

  if(oRuntime.addCommands(aArgv[1])){
    return -1;
  }

  oRuntime.run();

  // Afsluiten
  cout << endl << "Afgesloten :-)" << endl << endl;
  return 0;
};


