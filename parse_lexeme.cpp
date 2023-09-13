#include "parse_lexeme.hpp"

bool isLetter(char x) { return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'); }
bool isNumber(char x) { return (x >= '0' && x <= '9'); }

bool isSeparator(char _separator) {
    const char separators[] = {'(', ')', '[', ']', ','};
    for (auto separator: separators)
        if (_separator == separator) 
            return true;
    return false;
}

bool isOperation(char _op) {
    const char operations[] = {'+', '-', '*', '/'};
    for (auto op: operations)
        if (_op == op) return true;

    return false;
}

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

bool cmpPriority(char sym1, char sym2) {
    std::unordered_map<char, int> priority_table = {
        {'(', 0},
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2}
    };
    return priority_table[sym1] >= priority_table[sym2];
}

bool isOperationForParse(char _op) {
    const std::vector<char> operations = {'*', '/', '+', '-', '('};
    for (auto op : operations) {
        if (_op == op)
            return true;
    }
    return false;
}

bool calculate(std::string &str) {
    int i = 0;
    for (; i < str.length();) {
        if (str[i] == (char)0)
            str.erase(i, 1);

        if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-') {
            if (i - 2 >= 0 && (str[i - 2] == 'I' || str[i - 2] == 'N') && (str[i - 1] == 'I' || str[i - 1] == 'N')) {
                str.erase(i - 1, 2);
                i = i - 2;
            }
        }
        ++i;
    }

    if ((str[0] == 'I' || str[0] == 'N') && str.length() == 1)
        return true;
    return false;
}

std::string transformToPolishNotation(const std::string &str, int start_pos, int end_pos) {
    std::stack<char> operations;
    std::string polish_notation;
    bool flag_error = 0;
    for(int i = start_pos; i < end_pos && !flag_error;) {

        // добавление в выходную строчку x
        if (str[i] == 'I' || str[i] == 'N') {
            polish_notation.push_back(str[i++]);
        }
        // закидывание в стек операции
        if (isOperationForParse(str[i])) {
            if (!operations.empty() && (cmpPriority(operations.top(), str[i]) && str[i] != '(')) {
                polish_notation.push_back(operations.top());
                operations.pop();
            }
            operations.push(str[i++]);
        }
        // если встретилась закрыв. скобка, то ищем откр. скобку
        if (str[i] == ')') {
            while (!operations.empty() && operations.top() != '(') {
                polish_notation.push_back(operations.top());
                operations.pop();
            }

            if (operations.top() != '(')
                flag_error = 1;
                
            operations.pop();
            ++i;
        }
        // есил токены закончились, то выкидываем все операции из стека в выходную строчку
        if (i >= end_pos) {
            while (!operations.empty()) {
                polish_notation.push_back(operations.top());
                operations.pop();
            }
        }
    }
    return polish_notation;
}
