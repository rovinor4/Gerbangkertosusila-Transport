
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

void clearInput();
void pauseEnter();
void header(const string &title);
int inputInt(const string &label);
string inputLine(const string &label);
#endif