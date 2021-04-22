// 3.b compiler

#include "parser.hpp"

Parser::Parser() {
  nTokenSize_ = 0;
};

Parser::~Parser() {

};

//Tokenize the incomming line
bool Parser::parse(std::string sLine) {
  
  vector<string> tokens;
  tokenize(sLine, ' ', tokens);

  uint8_t nTokens = tokens.size();
  bool valid = false;
  if(nTokens < PARSER_MAX_TOKENS){                                        //check if the line isn't greater than PARSER_MAX_TOKENS
    if(nTokenSize_ < PARSER_MAX_TOKENSSIZE){                              //check is the token isnt't greater than PARSER_MAX_TOKENSSIZE
      for(uint8_t i = 0; i < tokens.size(); i++){
        std::size_t found = tokens.at(i).find("\r");                      //if "\r" is found remove it

        if(found != string::npos){
          tokens.at(i).erase(tokens.at(i).size()-1);
        }
      }
      if(valid = isLineValid(tokens)){
        aToken_.push_back(tokens);                                         //add to token list
      }
      nTokenSize_++;                                                      //add 1 to total token size
    } 
  } 
  return valid;
};

uint8_t Parser::getTokenSize(){
  return nTokenSize_;
}

vector<string> Parser::token(uint8_t nIndex){                           
  return aToken_[nIndex];
}

void Parser::printTokens(){                                             //print al the parsed tokens in the list
  for ( size_t i = 0; i < aToken_.size(); i++ )
  {
    for ( size_t j = 0; j < aToken_[i].size(); j++ ) cout << aToken_[i][j] + ' ' ;
    cout << std::endl;
  }
}

void Parser::tokenize(string &str, char delim, vector<string> &out){
	size_t start;
	size_t end = 0;

	while((start = str.find_first_not_of(delim, end)) != string::npos){
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

bool Parser::isLineValid(vector<string> sLine){
  switch (sLine.size())
  {
  case 4:
    if(sLine.at(0).compare("Knopjump")){
      if((sLine.at(2).compare("on") == 0) || (sLine.at(2).compare("off"))){
        return true;
      }else{
        return false;
      }
    }else{
      return false;
    }
    break;
  case 3:
    if(sLine.at(0).compare("Led") == 0){
      if((sLine.at(2).compare("on") == 0) || (sLine.at(2).compare("off"))){
        return true;
      }else{
        return false;
      }
    }else{
      return false;
    }
    break;
  case 2:
    if(sLine.at(0).compare("Wait")){
      return true;
    }else if(sLine.at(0).compare("Jump")){
      return true;
    }else if(sLine.at(0).compare("Label")){
      return true;
    }else{
      return false;
    }
    break;
  default:
    return false;
    break;
  }
}
