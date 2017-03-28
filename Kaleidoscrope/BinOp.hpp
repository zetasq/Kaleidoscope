//
//  BinOp.hpp
//  Kaleidoscrope
//
//  Created by Zhu Shengqi on 28/03/2017.
//  Copyright © 2017 Zhu Shengqi. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <map>

extern std::map<char, int> BinopPrecedence;
int GetTokPrecedence();
