#include <iostream>
#include "MyLibrary/MyLibrary.h"

using namespace std;

int main()
{
    cout << "Udemy course : Google Test & Google Mock!" << endl;

    cout << "Sqrt(9) = " << mySqrt(9) << endl;
    cout << "Addition of 5 + 3 = " << myAdd(5,3) << endl;

    vector<int> inputVector{1,-2, 3, -4, 5, -6, -7};
    cout << "In the vector there is " << countPositives(inputVector) << " positives numbers" << endl;

    return 0;
}
