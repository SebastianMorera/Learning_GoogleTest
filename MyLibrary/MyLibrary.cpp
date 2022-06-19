#include "MyLibrary.h"
#include <cmath>
#include <stdexcept>

// Basic tests
double mySqrt(double x)
{
    if(x < 0)
    {
        throw std::runtime_error("Negative argument"); // Exception
    }

    return sqrt(x);
}

int myAdd(int a, int b)
{
    return a + b;
}

bool isPositive(int x)
{
    return x >= 0;
}

int countPositives(vector<int> const& inputVector)
{
    return count_if(inputVector.begin(), inputVector.end(), isPositive);
}

// String
void toUpper(char *inputString)
{
    for(unsigned  i=0; i< strlen(inputString); i++)
    {
        inputString[i] = toupper(inputString[i]);
    }
}

// Test Fixture
Account::Account(): mBalance{0}
{}

void Account::deposit(double sum)
{
    mBalance += sum;
}

void Account::withdraw(double sum)
{
    if(mBalance < sum)
    {
        throw std::runtime_error("Insufficient funds");
    }
    mBalance -= sum;
}

double Account::getBalance() const
{
    return mBalance;
}

void Account::transfer(Account &to, double sum)
{
    withdraw(sum); // Will throw an error if not enough
    to.deposit(sum);
}

// Parameterized Tests
Validator::Validator(int low, int high): mLow{low}, mHigh{high}
{}

bool Validator::inRange(int valueToTest)
{
    return mLow <= valueToTest && valueToTest <= mHigh;
}