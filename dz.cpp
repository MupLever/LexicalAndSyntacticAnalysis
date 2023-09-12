#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stack>
#include "parse_lexeme.hpp"
using namespace std;

bool isLetter(char x){ return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'); }
bool isNumber(char x){ return (x >= '0' && x <= '9'); }

bool isSeparator(char _separator) {
  const char separators[] = {'(', ')', '[', ']', ','};
  for (auto separator: separators) {
    if (_separator == separator) return true;
  }
  return false;
}

bool isOperation(char _op) {
  const char operations[] = {'+', '-', '*', '/'};
  for (auto op: operations)
    if (_op == op) return true;

  return false;
}

int numberOfSignal(char signal) {
    const char signals[] = {'I', 'N', '[', ',', ']', ';'};
    for (int i = 0; i < 6; i++)
        if (signal == signals[i]) return i;
    return -1;
}

void printError(int arr[7][6], int state, char ch) {
    for (int signal = 0; signal < 6; ++signal) {
        if (arr[state][signal] != 0) {
            switch (signal) {
            case 0:
            case 1:
                std::cout << "Identify or literal was expected\n";
                break;
            case 2:
                std::cout << "Expected '[', but found " << ch << "\n";
                break;
            case 3:
                std::cout << "Expected ',', but found " << ch << "\n";
                break;
            case 4:
                std::cout << "Expected ']', but found " << ch << "\n";
                break;
            case 5:
                std::cout << "Expected ';', but found " << ch << "\n";
                break;
            }
        }
    }
}

void SyntacticAnalysis(std::string &str) {
    int automat[7][6] = {
        {1, 0, 0, 0, 0, 0},
        {0,	0, 2, 0, 0, 7},
        {3, 4, 0, 0, 0, 0},
        {0,	0, 0, 5, 6, 0},
        {0,	0, 0, 5, 6, 0},
        {3,	4, 0, 0, 0, 0},
        {0,	0, 0, 0, 0, 7}
    };

    int state = 0, signal = -1, k = 0;
    while(k < str.length()){
        if (k + 1 < str.length()) {
            if (str[k] == 'N' && str[k + 1] =='I') {
              std::cout << "Invalid identify name\n";
              break;
            }
        }

        if ((signal = numberOfSignal(str[k])) != -1)
            ++k;
        else
            break;

        if (automat[state][signal] != 0)
            state = automat[state][signal];
        else {
            printError(automat, state, str[k - 1]);
            break;
        }

        if (state == 2 || state == 5) {
            // for (int i = 0; i < str.length(); ++i)
            //     std::cout <<"[" << i << "]: " << str[i]  << std::endl;
            int comma_index = str.find_first_of(",]", k);

            if (comma_index != std::string::npos) {
                std::string tmp = parse(str, k, comma_index);
                if (!calculate(tmp)) {
                    // std::cout << "*****************************************" << std::endl;
                    // std::cout << calculate(tmp) << std::endl;
                    // std::cout << "*****************************************" << std::endl;
                    break;
                }
                str.replace(k, comma_index - k, "I");
                // std::cout << "*****************************************" << std::endl;
                // std::cout <<  str << std::endl;
                // std::cout << "*****************************************" << std::endl;
            }

        }
    }
    
    if (k == str.length() && state == 7)
        std::cout << "Successfully!\n";
    else 
        std::cout << "Unsuccessfully!\n";
}

void lexicalAnalysis(std::string &str) {
    std::string result, buf;
    trim(str);
    std::cout << str << std::endl;
    bool service = false;
    bool literal = false;
    bool letter = false;
    bool space = false;

    for (int i = 0; i < str.length();) {
        if (isNumber(str[i])) {
            std::cout << "Literal: ";
            while (isNumber(str[i]))
                std::cout << str[i++];
  
            result.push_back('N');
            literal = true;
            std::cout << "\n";
        }

        if (isOperation(str[i]) || isSeparator(str[i])) {
            std::cout << "Service symbol: " << str[i] << "\n";
            service = true;
            result.push_back(str[i++]);
        }

        if (isLetter(str[i])) {
            buf = "";
            while (isLetter(str[i]) || isNumber(str[i]))
                buf.push_back(str[i++]);
            letter = true;

            result.push_back('I');
            std::cout << buf << std::endl;
        }
    
        if (str[i] == ' ') {
            ++i;
            space = true;
        }
      
        if (!(letter || literal || service || space)) {
            std::cout << "Wrong symbol: " << str[i + 1] << "\n";
            return;
        }

        letter = false;
        literal = false;
        service = false;
        space = false;
    }
    result += ";";
    std::cout << "result: " << result << std::endl;
    SyntacticAnalysis(result);
    // std::string tmp = parse(result);
    // std::cout << calculate(tmp) << std::endl;
    return;
}

int main() {
    string input_string, end = "end";
    std::cout << "Input string or end: " ;
    std::getline(std::cin, input_string);
    while(input_string.compare(end)) {
        lexicalAnalysis(input_string);
        std::cout << "Input string or end:";
        std::getline(std::cin, input_string);  
  }
  return 0;
}
