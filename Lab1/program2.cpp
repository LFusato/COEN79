#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <cassert>
using namespace std;

int main()
{
    string digits;                          //create string to hold inputs

    cout << "Enter 10 digits:";             //get user input for 10 digits
    cin >> digits;

    int dLength = digits.length();          //find length of input

    assert(dLength == 10);                  //confirm input is exactly 10 digits

    for(int i = 0; i < 5; i++) {            //Run through print for 5 lines
        cout << setw(10 + (2*i));           //set width, increases the more lines that are printed
        for(int j = 0; j < 10; j++) {       //print input in reverse order
            cout << digits[9-j];
        }
        cout << "          ";               //add space
        for(int k = 0; k < 10; k++) {       //print input in non-reverse order
            cout << digits[k];
        }
        cout << endl;                       //go to new line
    }

    return EXIT_SUCCESS;
}