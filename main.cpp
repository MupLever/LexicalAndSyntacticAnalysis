#include "parse_lexeme.hpp"
#include <iostream>

int numberOfSignal(const char signal) {
    const char signals[] = {'I', 'N', '[', ',', ']', ';'};
    for (int i = 0; i < 6; i++)
        if (signal == signals[i]) return i;
    return -1;
}

void printError(const int arr[7][6], const int state, const char ch) {
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

void syntacticAnalysis(std::string &str) {
    int automat[7][6] = {
        {1, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 7},
        {3, 4, 0, 0, 0, 0},
        {0, 0, 0, 5, 6, 0},
        {0, 0, 0, 5, 6, 0},
        {3, 4, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 7}
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
            int comma_index = str.find_first_of(",]", k);

            if (comma_index != std::string::npos) {
                std::string tmp = transformToPolishNotation(str, k, comma_index);
                if (!calculate(tmp))
                    break;
                str.replace(k, comma_index - k, "I");
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
      
        if (letter && literal && service && space) {
            std::cout << "Wrong symbol: " << str[i + 1] << "\n";
            return;
        }

        letter = false;
        literal = false;
        service = false;
        space = false;
    }
    std::cout << "result: " << result << std::endl;
    result += ";";
    syntacticAnalysis(result);
    return;
}

int main() {
    std::string input_string, end = "end";
    std::cout << "Input string or end: ";
    std::getline(std::cin, input_string);
    while (input_string.compare(end)) {
        lexicalAnalysis(input_string);
        std::cout << "Input string or end:";
        std::getline(std::cin, input_string);  
    }
    return 0;
}
