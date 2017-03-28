//
//  BinOp.cpp
//  Kaleidoscrope
//
//  Created by Zhu Shengqi on 28/03/2017.
//  Copyright © 2017 Zhu Shengqi. All rights reserved.
//

#include "BinOp.hpp"
#include "parser.hpp"
#include <map>

/// BinopPrecedence - This holds the precedence for each binary operator that is defined
std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
int GetTokPrecedence() {
  if (!isascii(CurTok)) {
    return -1;
  }
  
  // Make sure it's a declared binop.
  int TokPrec = BinopPrecedence[CurTok];
  if (TokPrec <= 0) return -1;
  return TokPrec;
}
