#include <stack>
#include <string>
using namespace std;

#ifndef INFIXTOPOSTFIX_H
#define INFIXTOPOSTFIX_H

class infixToPostfix {
  public:
  string spaceCanceller(string infix);
  bool isCheckedParantheses(string infix);
  bool isOperator(char c);
  int precedence(char c);
  string toPostfix(string infix);

};

#endif //INFIXTOPOSTFIX_H