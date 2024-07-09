

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "ArgumentManager.h"
using namespace std;

bool followsBracketOrder(const string &line) {
  priority_queue<char, vector<char>, greater<char> > bracketOrder;

  for (char c : line) {
    if (c == '(' || c == '[' || c == '{') {
      bracketOrder.push(c);
    }
    else if (c == ')' || c == ']' || c == '}') {
      if (bracketOrder.empty()) {
        return false; 
      }

      char top = bracketOrder.top();
      if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
          (c == '}' && top != '{')) {
        return false; 
      }

      bracketOrder.pop(); 
    }
  }
  return bracketOrder.empty();
}

/*
Part I left for group memebers 

Current issue with the code is that it is not able to recognize if the
brackets are in the correct order or not

Curly Brackets { } are only enclosed in other curly brackets
Square Brackets [ ] are only enclosed in either curly or square brackets
Round Brackets ( ) are enclosed in either curly or square or round
brackets
These are guidlines to be followed

Current output
Invalid
}[]}
(][}}
}}}
Valid
{[()]}
{}
[()]
(())
[{()}] This is invalid. Shouldnt be in Valid section

*/

bool areBracketsValid(const string &line) {
  if (followsBracketOrder(line)) {
    stack<char> bracketStack;

    for (char c : line) {
      if (c == '(' || c == '[' || c == '{') {
        bracketStack.push(c);
      } else if (c == ')' || c == ']' || c == '}') {
        if (bracketStack.empty()) {
          return false; 
        }

        char top = bracketStack.top();
        if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
            (c == '}' && top != '{')) {
          return false; 
        }

        bracketStack.pop(); 
      }
    }

    return bracketStack.empty(); 
  } else {
    return false;
  }
}

int main(int argc, char *argv[]) {

  ArgumentManager am(argc, argv);

   ifstream inputFile(am.get("input"));
   ofstream outputFile(am.get("output"));

  //  ifstream inputFile("/Users/saadbeg/Documents/SEM 3/Data Structures/ga2/input1.txt");
  //  ofstream outputFile("output22.txt");

  if (!inputFile.is_open()) {
    cerr << "Failed to open the input file." << endl;
    return 1;
  }

  string line;
  vector<string> validLines;
  vector<string> invalidLines;
  bool hasValidLines = false;
  bool hasInvalidLines = false;

  while (getline(inputFile, line)) {
    if (line.empty()) {
      continue;
    }
    if (areBracketsValid(line)) {
      validLines.push_back(line);
      hasValidLines = true;
    } else {
      invalidLines.push_back(line);
      hasInvalidLines = true;
    }
  }

  if (hasInvalidLines) {
    outputFile << "Invalid" << endl;
    for (const string &invalidLine : invalidLines) {
      outputFile << invalidLine << endl;
    }
  }

  if (hasValidLines) {
    outputFile << "Valid" << endl;
    for (const string &validLine : validLines) {
      outputFile << validLine << endl;
    }
  }

  inputFile.close();

  return 0;
}

