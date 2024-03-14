#include <iostream>
#include <string>
#include <stack>
using namespace std;


// Input: A string of brackest, for example:  '(' ,  ')' ,  '['  and  ']'
// Output: True if chain of brackets is valid and return False if it is invalid

bool validBrackets(string input) {
  stack<char> my_stack;
  
  for (char x : input) { // For each character
  // TODO
  
    // If we open a bracket, push it to the stack
    if (x == '[' || x == '('){
      my_stack.push(x);
      
    }

    // If we are closing a bracket:
    else if (x == ']' || x == ')'){

      // If the stack is empty, we don't have a match. So, return false
      if (my_stack.empty()){
        return false;
      }
      // If we have a matching bracket, remove it from the stack so we don't match it again
      else if (my_stack.top() == '[' && x == ']' || my_stack.top() == '(' && x == ')'){
        my_stack.pop();
      }
      // If there is a bracket in the stack but it   doesn't match -> return false
      else if (x == ']' || x == ')'){
        return false;
      }

    }
  }
  
  // If the stack is empty, all brackets matched -> return true
  // If the stack isn't empty, we have unmatched brackets -> return false
  return my_stack.empty();
}


int main() {
  // Test the stack implementation
  stack<char> my_stack;

  my_stack.push('a');
  my_stack.push('b');
  my_stack.push('c');

  // If the stack implementation is correct we will see c b a
  while (!my_stack.empty()) {
    std::cout << my_stack.top() << " ";
    my_stack.pop();
  }

  std::cout << endl << endl;

  // Test validBrackets
  
  // Test cases
  string brackets0 = "[]([]())"; // Valid
  string brackets1 = "[][[]())"; // Invalid
  string brackets2 = "()()[()()])[[]]"; // Invalid
  string brackets3 = ""; // Valid
  string brackets4 = "("; // Invalid

  std::cout << "Is \"" << brackets0 << "\" valid? " << validBrackets(brackets0) << endl;
  std::cout << "Is \"" << brackets1 << "\" valid? " << validBrackets(brackets1) << endl;
  std::cout << "Is \"" << brackets2 << "\" valid? " << validBrackets(brackets2) << endl;
  std::cout << "Is \"" << brackets3 << "\" valid? " << validBrackets(brackets3) << endl;
  std::cout << "Is \"" << brackets4 << "\" valid? " << validBrackets(brackets4) << endl;

  return 0;
}
