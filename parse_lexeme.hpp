#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm> 
#include <unordered_map>

void ltrim(std::string &s);
void rtrim(std::string &s);

// функция удаления пробелов
void trim(std::string &s);


// это операторы и функции для алгоритма сортировочной станции?
bool isOperationForParse(char c);

// сравнивает приоритеты операций
bool cmpPriority(char sym1, char sym2);

bool calculate(std::string &str);

// алгоритм сортировочной станции
std::string parse(const std::string &str, int start_pos, int end_pos);
