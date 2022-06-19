#ifndef TEACHINGPROJECT3_LIBRARY_H
#define TEACHINGPROJECT3_LIBRARY_H

#include <iostream>
#include "algorithm"

#include <cctype>
#include <string.h>
#include <vector>

using namespace std;

double mySqrt(double x);
int myAdd(int a, int b);
bool isPositive(int x);
int countPositives(vector<int> const& inputVector);

void toUpper(char *inputString);

class Account
{
public:
    Account();
    void deposit(double sum);
    void withdraw(double sum);
    double getBalance() const;
    void transfer(Account& to, double sum);

private:
    double mBalance;
};

class Validator
{
    public:
        Validator(int low, int high);
        bool inRange(int valueToTest);

    private:
        int mLow, mHigh;
};

#endif //TEACHINGPROJECT3_LIBRARY_H