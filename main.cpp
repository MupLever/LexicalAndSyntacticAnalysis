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
    const int automat[7][6] = {
        {1, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 7},
        {3, 4, 0, 0, 0, 0},
        {0, 0, 0, 5, 6, 0},
        {0, 0, 0, 5, 6, 0},
        {3, 4, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 7}
    };

    int state = 0, signal = -1, cur_token = 0;
    while (cur_token < str.length()) {
        if (cur_token + 1 < str.length() && str[cur_token] == 'N' && str[cur_token + 1] =='I') {
            std::cout << "Invalid identify name\n";
            break;
        }

        if ((signal = numberOfSignal(str[cur_token])) != -1)
            ++cur_token;
        else
            break;

        if (automat[state][signal] != 0) {
            state = automat[state][signal];
        } else {
            printError(automat, state, str[cur_token - 1]);
            break;
        }

        if (state == 2 || state == 5) {
            int comma_index = str.find_first_of(",]", cur_token);

            if (comma_index != std::string::npos) {
                std::string tmp = transformToPolishNotation(str, cur_token, comma_index);
                if (!calculate(tmp))
                    break;
                str.replace(cur_token, comma_index - cur_token, "I");
            }
        }
    }
    
    if (cur_token == str.length() && state == 7)
        std::cout << "Successfully!\n";
    else 
        std::cout << "Unsuccessfully!\n";
}

void lexicalAnalysis(std::string &str) {
    std::string result, buf;
    trim(str);
    std::cout << str << std::endl;
    for (int i = 0; i < str.length();) {
        if (isNumber(str[i])) {
            buf = "";
            while (isNumber(str[i]))
                buf.push_back(str[i++]);

            result.push_back('N');
            std::cout << "Literal: " << buf << std::endl;
        } else if (isOperation(str[i]) || isSeparator(str[i])) {
            std::cout << "Service symbol: " << str[i] << "\n";
            result.push_back(str[i++]);
        } else if (isLetter(str[i])) {
            buf = "";
            while (isLetter(str[i]) || isNumber(str[i]))
                buf.push_back(str[i++]);

            result.push_back('I');
            std::cout << "Identify: " << buf << std::endl;
        } else if (str[i] == ' ') {
            ++i;
        } else {
            std::cout << "Wrong symbol: " << str[i] << "\n";
            return;
        }
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
