#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char *argv[])
{
    string longword;                                    //string to hold current word
    assert(argc == 2);                                  //confirm a text file is put in command line
    ifstream inputFile (argv[1]);                       //open file

    assert(inputFile.is_open());                        //confirm file is open
    while(inputFile >> longword) {                      //run loop while reading file
        int wLength = longword.length();                //find length of first word
        for(int i = 0; i < wLength; i++) {              //run through each character of word
            if(isalnum(longword[i]) == 0) {             //if character is not alpha numeric, erase the character
                longword.erase (i,1);
                i--;                                    //decrement to account for deletion
                wLength--;                              //decrement total length to account for deletion
            }
            else
            {
                longword[i] = toupper(longword[i]);     //if alpha numeric, change to upper case if possible
            }
            
        }
        if(wLength >= 10) {                             //if the updated word is over 10 characters, print
            cout << longword << endl;
        }

    }
    
    inputFile.close();                                  //close file

    return EXIT_SUCCESS;
}