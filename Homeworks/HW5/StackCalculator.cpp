#include <iostream>
#include "StackCalculator.hpp"


using namespace std;
/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-")
      return false;

    else if(s.size() > 1 && s[0] == '-')
      s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++){
      if(!isdigit(s[i]) && s[i] != '.')
        return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}

StackCalculator::StackCalculator()
{
  //TODO:
  stackHead = nullptr;
}

StackCalculator::~StackCalculator()
{
  //TODO:
  Operand* temp = stackHead;
  while(temp != nullptr) {
    delete temp;
    temp = temp->next;
  }
  stackHead = nullptr;
}

bool StackCalculator::isEmpty()
{
	//TODO:
  if (stackHead == nullptr) {
    return true;
  }
  return false;
}

void StackCalculator::push(float number)
{
  //TODO:
  Operand* temp = new Operand;
  temp->number = number;
  temp->next = stackHead;
  stackHead = temp;
}

void StackCalculator::pop()
{
	//TODO:
  if (!isEmpty()) {
    Operand* temp = new Operand;
    temp = stackHead;
    stackHead = stackHead->next;
    delete temp;
  } 
  else {
    cout << "Stack empty, cannot pop an item." << endl;
  }
}

Operand* StackCalculator::peek()
{
	//TODO:
  if (!isEmpty()) {
    return stackHead;
  } 
  else {
    cout << "Stack empty, cannot peek." << endl;
    return nullptr;
  }
}

bool StackCalculator:: evaluate(string* s, int size)
{
  /*TODO: 1.scan the array from the end
          2.Use isNumber function to check if the input is an operand
          3.push all operands to the stack
          4.If operator take two element of from the stack,
            compute and put the result back in stack
          5.Handle the boundery cases as required.
          6.Read the writeup for more details
  */
   float temp1;
   float temp2;
   float result;
   size--;
   while(size>=0){
     if(isNumber(s[size])){
       //push number to stack
       push(stof(s[size])); 
     }
     else if (s[size] == "+"){
       if(stackHead == NULL || stackHead->next == NULL){
         cout << "err: not enough operands" << endl;
         return false;
       }
       temp1 = peek()->number;
       pop();
       temp2 = peek()->number;
       pop();
       result = temp1 + temp2;
       push(result);
     }
      else if (s[size] == "*"){
       if(stackHead == NULL || stackHead->next == NULL){
         cout << "err: not enough operands" << endl;
         return false;
       }
       temp1 = peek()->number;
       pop();
       temp2 = peek()->number;
       pop();
       result = temp1 * temp2;
       push(result);
     }
     else{
       cout << "err: invalid operation" << endl;
       return false; 
     }
     size--;
   }

    return true;
}


