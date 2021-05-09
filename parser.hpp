// 3.b compiler

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

  #include <iostream>
  #include <stdexcept>
  #include <stdint.h>
  #include <string>
  #include <vector>

  using namespace std;

  #define PARSER_MAX_TOKENS 5
  #define PARSER_MAX_TOKENSSIZE 100
  


  class Parser {
    public:
      Parser();
      ~Parser();
      vector<string> parse(string sLine);
    private:
      vector<string> tokenize(string &str, char delim);
      string sendError(string sLineNumber, string );
      string isLineValid(vector<string> sLine);
      uint8_t nTokenSize_;
  };

#endif // _PARSER_HPP_