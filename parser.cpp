// 3.b compiler

#include "parser.hpp"

Parser::Parser() {
  nTokenSize_ = 0;
};

Parser::~Parser() {

};

/** 
 * @brief Tokenize the incomming line
 * @param sLine The line to be tokenized
 * @return A tokenized string
 * */
vector<string> Parser::parse(std::string sLine) {
  
  vector<string> tokens;
  tokens = tokenize(sLine, ' ');

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
      if(msg == "NULL"){
        nTokenSize_++;                                                     //add 1 to total token size
        return tokens;                                                     //add to token list
      }else{
        throw invalid_argument(msg);                                       //if error detected, throw an error
      }                                               
    }else{
      throw invalid_argument("Maximum command size reached. Max size = " + to_string(PARSER_MAX_TOKENSSIZE));
    }
  }else{
    throw invalid_argument("Too many arguments. Max arguments = " + to_string(PARSER_MAX_TOKENS));
  }
  return {"NULL"};
};

/**
 * @brief Check if tokenized line doesn't contain any errors
 * @param sLine The tokenized line to be checked
 * @return if the line is valid
 * */
string Parser::isLineValid(vector<string> sLine){
  switch (sLine.size())
  {
  case 4:
    if(sLine.at(0) == "Jumpknop"){
      if((sLine.at(2) == "ja") || (sLine.at(2) == "nee")){
        return "NULL";
      }else{
        return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
          "Error: '" + sLine.at(2) + "' is not a Knop state. A Knop state can only be <ja:nee>";
      }
    }else if(sLine.at(0) == "Wait"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Jump"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Label"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Led"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 3";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: '" + sLine.at(0) + "' is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  case 3:
    if(sLine.at(0) == "Led"){
      if((sLine.at(2) == "on") || (sLine.at(2) == "off")){
        return "NULL";
      }else{
        return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
          "Error: '" + sLine.at(2) + "' is not a Led state. A Led state can only be <on:off>";
      }
    }else if(sLine.at(0) == "Wait"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Jump"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Label"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too many arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Jumpknop"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 4";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: '" + sLine.at(0) + "' is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  case 2:
    if(sLine.at(0) == "Wait"){
      return "NULL";
    }else if(sLine.at(0) == "Jump"){
      return "NULL";
    }else if(sLine.at(0) == "Label"){
      return "NULL";
    }else if(sLine.at(0) == "Led"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 3";
    }else if(sLine.at(0) == "Jumpknop"){
       return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 4";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: '" + sLine.at(0) + "' is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  case 1:
    if(sLine.at(0) == "Wait"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Jump"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Label"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 2";
    }else if(sLine.at(0) == "Led"){
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 3";
    }else if(sLine.at(0) == "Jumpknop"){
       return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: too few arguments for '" + sLine.at(0) + "'. Arguments size is " + to_string(sLine.size()) + ". This should be 4";
    }else{
      return "Syntax error at line: " + to_string(nTokenSize_ + 1) + "\n" + 
        "Error: '" + sLine.at(0) + "' is an unknown keyword. Available keywords: <Led:Wait:Jump:Knopjump:Label>";
    }
    break;
  default:
    return "Error at line " + to_string(nTokenSize_ + 1);
    break;
  }
}

vector<string> Parser::tokenize(string &str, char delim){
	size_t start;
	size_t end = 0;
  vector<string> out;
	while((start = str.find_first_not_of(delim, end)) != string::npos){
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
  return out;
}
