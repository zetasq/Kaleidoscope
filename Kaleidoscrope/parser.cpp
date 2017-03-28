//
//  parser.cpp
//  Kaleidoscrope
//
//  Created by Zhu Shengqi on 27/03/2017.
//  Copyright © 2017 Zhu Shengqi. All rights reserved.
//

#include "parser.hpp"
#include "lexer.hpp"
#include "AST.hpp"

/// CurTok/getNextToken - Provide a simple token buffer. CurTok is the current
/// token the parser is looking at.  getNextToken reads another token from the
/// lexer and updates Curtok with its results.

int CurTok;
static int getNextToken() {
  return CurTok = gettok();
}

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str) {
  fprintf(stderr, "LogError: %s\n", Str);
  return nullptr;
}

std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
  LogError(Str);
  return nullptr;
}

/// numberexpr ::= number
static std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken(); // consume the number
  return std::move(Result);
}

/// parenexpr ::= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr() {
  getNextToken(); // eat (.
  auto V = ParseExpression();
  if (!V) {
    return nullptr;
  }
  
  if (CurTok != ')') {
    return  LogError("expected ')'");
  }
  
  getNextToken();
  return V;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;
  
  getNextToken(); // eat identifier
  
  if (CurTok != '(') { // Simple variable ref.
    return std::make_unique<VariableExprAST>(IdName);
  }
  
  // Call.
  getNextToken(); // eat (
  std::vector<std::unique_ptr<ExprAST>> Args;
  if (CurTok != ')') {
    while (true) {
      if (auto Arg = ParseExpression()) {
        Args.push_back(std::move(Arg));
      } else {
        return nullptr;
      }
      
      if (CurTok == ')') {
        break;
      }
      
      if (CurTok != ',') {
        return LogError("Expected ')' or ',' in argument list");
      }
      
      getNextToken();
    }
  }
  
  // Eat the ')'.
  getNextToken();
  
  return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
static std::unique_ptr<ExprAST> ParsePrimary() {
  switch (CurTok) {
    case tok_identifier:
      return ParseIdentifierExpr();
    case tok_number:
      return ParseNumberExpr();
    case '(':
      return ParseParenExpr();
    default:
      return LogError("unknown token when expecting an expression");
  }
}

/// expression
///   ::= primary binoprhs
///
static std::unique_ptr<ExprAST> ParseExpression() {
  auto LHS = ParsePrimary();
  if (!LHS) {
    return nullptr;
  }
  
  return ParseBinOpRHS(0, std::move(LHS));
}
