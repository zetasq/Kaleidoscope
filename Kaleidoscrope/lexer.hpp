//
//  lexer.hpp
//  Kaleidoscrope
//
//  Created by Zhu Shengqi on 26/03/2017.
//  Copyright © 2017 Zhu Shengqi. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>

enum Token {
  tok_eof = -1,
  
  tok_def = -2,
  tok_extern = -3,
  
  tok_identifier = -4,
  tok_number = -5,
};

extern std::string IdentifierStr;
extern double NumVal;

int gettok();
