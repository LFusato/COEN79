#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
using namespace std;

int main()
{
    string phrase;                                  //create string to hold input
    int alphaNum = 0;                               //# of alpha numeric variable
    int nonAlphaNum = 0;                            //# of non alpha numeric variable

    cout << "Enter phrase:";                        //get user input for phrase
    getline (cin,phrase);

    int pLength = phrase.length();                  //find length of input

    for (int i = 0; i < pLength; i++) {             //runs through entire length of input
        if(phrase[i] != ' ') {                      //when the read letter is not a space 
            if(isalnum(phrase[i]))                  //if a letter or number increment counter
                alphaNum++;
            else                                    //if not a letter or number increment counter
                nonAlphaNum++;
        }
    }

    cout << "There are " << alphaNum << " alphanumeric characters and " << nonAlphaNum << " non-alphanumeric characters.\n";                //print results
    return EXIT_SUCCESS;
}