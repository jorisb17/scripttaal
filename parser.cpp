// 3.b compiler

#include "parser.hpp"

Parser::Parser() {
  nTokenSize_ = 0;
};

Parser::~Parser() {

};

//Tokenize the incomming line
vector<string> Parser::parse(std::string sLine) {
  
  vector<string> tokens;
  tokenize(sLine, ' ', tokens);

  uint8_t nTokens = tokens.size();
  if(nTokens < PARSER_MAX_TOKENS){                                        //check if the line isn't greater than PARSER_MAX_TOKENS
    if(nTokenSize_ < PARSER_MAX_TOKENSSIZE){                              //check is the token isnt't greater than PARSER_MAX_TOKENSSIZE
      for(uint8_t i = 0; i < tokens.size(); i++){
        std::size_t found = tokens.at(i).find("\r");                      //if "\r" is found remove it

        if(found != string::npos){
          tokens.at(i).erase(tokens.at(i).size()-1);
        }
      }
      string msg = isLineValid(tokens);
      if(msg.compare("NULL") == 0){
        nTokenSize_++;                                                     //add 1 to total token size
        return tokens;                                                     //add to token list
      }else{
        throw invalid_argument(msg);
      }                                               
    }else{
      throw invalid_argument("Maximum command size reached. Max size = " + to_string(PARSER_MAX_TOKENSSIZE));
    }
  }else{
    throw invalid_argument("Too many arguments. Max arguments = " + to_string(PARSER_MAX_TOKENS));
  }
  return {"NULL"};
};

void Parser::tokenize(string &str, char delim, vector<string> &out){
	size_t start;
	size_t end = 0;

	while((start = str.find_first_not_of(delim, end)) != string::npos){
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

string Parser::isLineValid(vector<string> sLine){
  switch (sLine.size())
  {
  case 4:
    if(sLine.at(0).compare("Jumpknop") == 0){
      if((sLine.at(2).compare("ja") == 0) || (sLine.at(2).compare("nee") == 0)){
        return "NULL";
      }else{
        return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
          "Error: " + sLine.at(2) + " is not a Knop state. A Knop state can only be <ja:nee>";
      }
    }else if(sLine.at(0).compare("Wait") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Jump") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Label") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Led") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 3";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: " + sLine.at(0) + " is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  case 3:
    if(sLine.at(0).compare("Led") == 0){
      if((sLine.at(2).compare("on") == 0) || (sLine.at(2).compare("off") == 0)){
        return "NULL";
      }else{
        return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
          "Error: " + sLine.at(2) + " is not a Led state. A Led state can only be <on:off>";
      }
    }else if(sLine.at(0).compare("Wait") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Jump") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Label") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Jumpknop") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 4";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: " + sLine.at(0) + " is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  case 2:
    if(sLine.at(0).compare("Wait") == 0){
      return "NULL";
    }else if(sLine.at(0).compare("Jump") == 0){
      return "NULL";
    }else if(sLine.at(0).compare("Label") == 0){
      return "NULL";
    }else if(sLine.at(0).compare("Led") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 3";
    }else if(sLine.at(0).compare("Jumpknop") == 0){
       return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 4";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: " + sLine.at(0) + " is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  case 1:
    if(sLine.at(0).compare("Wait") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Jump") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Label") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0).compare("Led") == 0){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 3";
    }else if(sLine.at(0).compare("Jumpknop") == 0){
       return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for " + sLine.at(0) + ". Arguments size is " + to_string(sLine.size()) + ". This should be 4";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: " + sLine.at(0) + " is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  default:
    return "Error at line " + to_string(nTokenSize_ + 1);
    break;
  }
}
