// 3.b compiler

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

  #include <iostream>
  #include <stdint.h>
  #include <string>
  #include <vector>

  using namespace std;

  #define PARSER_MAX_TOKENS 5
  #define PARSER_MAX_TOKENSSIZE 50
  


  class Parser {
    public:
      Parser();
      ~Parser();
      uint8_t parse(string sLine);
      vector<string> token(uint8_t nIndex);
      void printTokens();
      uint8_t getTokenSize();
    private:
      void tokenize(string &str, char delim, vector<string> &out);
      bool isLineValid(vector<string> sLine);
      vector<vector<string>> aToken_;
      uint8_t nTokenSize_;
  };

#endif // _PARSER_HPP_