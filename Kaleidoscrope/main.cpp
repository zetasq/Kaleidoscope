//
//  main.cpp
//  Kaleidoscrope
//
//  Created by Zhu Shengqi on 26/03/2017.
//  Copyright © 2017 Zhu Shengqi. All rights reserved.
//

#include <iostream>
#include "BinOp.hpp"

int main(int argc, const char * argv[]) {
    // Install standard binary operators.
    // 1 is lowest precedence.
  BinopPrecedence['<'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40; // highest.
  
  return 0;
}
