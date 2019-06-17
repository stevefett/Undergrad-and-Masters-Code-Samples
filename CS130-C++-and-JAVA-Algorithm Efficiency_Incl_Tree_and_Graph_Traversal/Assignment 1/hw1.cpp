//Steven Salmons
//HW#1
//CSC 130

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
using namespace std;

//Tests to see if a char is an operand.
bool isOperand (char testVal)
{
   if (((testVal >= 'a') && (testVal <= 'z')) || ((testVal >= '0') && 
  (testVal <= '9')) || ((testVal >= 'A') && (testVal <= 'Z')))
   {  
      return true;
   }
   else return false;
}

//Tests to see if a character is an open-bracket.
bool openParen (char testVal)
{
   if ((testVal == '(') || (testVal == '{') || (testVal == '['))
      return true;
   else 
      return false;
}

//Tests to see if a character is a close-bracket.
bool closeParen (char testVal)
{
   if ((testVal == ')') || (testVal == ']') || (testVal == '}'))
      return true;
   else
      return false;
}

//Tests to see if a character is an operator.
bool isOperator (char testVal)
{
   if ((testVal == '*') || (testVal == '+') || (testVal == '-') || 
      (testVal == '/') || openParen(testVal) || closeParen(testVal))     
   { 
      return true;
   }
   else
      return false;
}

//Assigns a priority to operators. 
//Bracket ')' is a special case since it has no character
//between it on the ascii chart, unlike other brackets.
int prio(char testVal)
{
   switch(testVal)
   {
      case '+':
         return 1;
         break;
      case '-':
         return 1;
         break;
      case '/': 
         return 2;
         break;
      case '*':
         return 2;
         break;
      case ')':
         return -2;
         break;
      default: 
         return -1;
         break;
   }
}

//Uses a stack to make sure the brackets in the expression match right.
bool parenMatch(string input)
{
   stack<char> parenStack;
   string inputStr = input;
   string::iterator it;
   for (it = inputStr.begin(); it < inputStr.end(); it++)
   {
      if ((isOperator(*it)) && (prio(*it) < 0))
      {
         if (parenStack.empty())  
            parenStack.push(*it);
         else if ((prio(*it) == -2) && (*it == (parenStack.top() + 1)))
            parenStack.pop();
         else if (*it == (parenStack.top() + 2))
            parenStack.pop();
         else 
            parenStack.push(*it);
      }
    }
    if (!parenStack.empty())
       return false;
    else
       return true;
}
     
//Main function, converting infix input string to postfix output str.
//Returns an error string if something went wrong.
string infixConv (string input)
{
   stack<char> postStack;
   string convertedStr, inputStr = input;
   string::iterator it;

   //Runs the parenthesis check first to make sure it's okay.
   if (!parenMatch(inputStr))
   {
      return "Parenthesis do not match.  Invalid expression.";
   }
   
   //String is OK, so we must traverse it.
   else
   {
      for (it = inputStr.begin(); it < inputStr.end(); it++)
      {
	   //If it's an operand, send it to the output string.
         if (isOperand(*it))
            convertedStr+=(*it);

         //If it's an operator, run operator logic.
         else if (isOperator(*it))
         {
            bool done = false;
            while (!done)
            {
		   //If the stack is empty, put the operator on it.
               if (postStack.empty())
               {
                  postStack.push(*it);
                  done = true;
               }
               //If it's an open paren, push it on stack.
               else if (openParen(*it))
               {
                  postStack.push(*it);
                  done = true;
               }
               //If its a close paren, pop until it's equivalent open  
               //is found.
               else if (closeParen(*it))
               {
                  int bracketFind = 0;
                  if (*it == ')')
                    bracketFind = 1;
                  else
                    bracketFind = 2;
                  while (postStack.top() != (*it - bracketFind))
                  {
                     convertedStr += postStack.top();
                     postStack.pop();
                  }
                  postStack.pop();
                  done = true;
               }
               //If the operator has higher priority, push it.
               else if (prio(postStack.top()) < prio(*it))
               {
                  postStack.push(*it);
                  done = true;
               }
               //If the operator has lesser or equiv priority, pop 
               //the stack and evaluate char over again.
               else if (prio(postStack.top()) >= prio(*it))
               {
                  convertedStr+=postStack.top();
                  postStack.pop();
               }
            }
         }
         //If its not an operand or operator, the expression is wrong.
         else 
         {
            return "Illegal expression, cannot convert.";         
         }        
      }  
      //Once traversal is done, pop the rest of the stack.
      if (!postStack.empty())
      {
         for (int s=0; s <= postStack.size(); s++)
         {
            convertedStr+=postStack.top();
            postStack.pop();
         }
      }   
      //Return the finished postfix string.
      return convertedStr;
   }
}

int main () {
  string infixStr, postfixStr;
  cout <<"Enter an inorder expression [ie: a+(b*c)]: ";
  getline (cin, infixStr);
  postfixStr = infixConv(infixStr);
  cout <<postfixStr <<endl;
  return 0;
}
