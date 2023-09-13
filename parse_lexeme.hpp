#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm> 
#include <unordered_map>

bool isLetter(char x);

bool isNumber(char x);

bool isSeparator(char _separator);

bool isOperation(char _op);

// функция удаления пробелов слева
void ltrim(std::string &s);

// функция удаления пробелов справа
void rtrim(std::string &s);

// функция удаления пробелов слева и справа
void trim(std::string &s);


// это операторы и функции для алгоритма сортировочной станции?
bool isOperationForParse(char c);

// сравнивает приоритеты операций
bool cmpPriority(char sym1, char sym2);

// Валидирует строку токенов в польской нотации
bool calculate(std::string &str);

// алгоритм сортировочной станции
std::string transformToPolishNotation(const std::string &str, int start_pos, int end_pos);
