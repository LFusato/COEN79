// FILE: mystring.cpp
// CLASS IMPLEMENTED: string

// INVARIANTS for the string class:
// 
//  

#include <cassert>   // Provides assert
#include <cstdlib>  // Provides size_t
#include <iostream>
#include "mystring.h"
#include <cstring>

using namespace std;
using namespace coen79_lab5;

namespace coen79_lab5 {
    // Constructor, copy constructor, and destructor
    string::string(const char str[ ]) {
        current_length = strlen(str); // String has length of given string
        allocated = current_length + 1; // Allocate memory for the string 
        characters = new char[allocated]; //create dynamic char array
        strncpy(characters, str, allocated); //copy characters into array
    }

    string::string(char c) {
        current_length = 1; // String has a current length of 1
        allocated = 2; // Allocate memory for the character 
        characters = new char[allocated];
        characters[0] = c; //set the first character to c
        characters[1] = '\0'; //add the end of string marking
    }       

    string::string(const string& source) {
        current_length = source.current_length; // Set all private variables to source's
        allocated = source.allocated; 
        characters = new char[allocated];
        strncpy(characters, source.characters, allocated);
    }

    string::~string( ) {
        delete [] characters;
    }
    
    // Modification member functions
    void string::operator +=(const string& addend) {
        cout << "Operator += string opened" << endl;
        current_length += addend.current_length;
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend.characters, current_length);
        //characters[allocated] = '\0';
    }

    void string::operator +=(const char addend[ ]) {
        cout << "Operator += const opened" << endl;
        current_length += strlen(addend);
        allocated = current_length + 1;
        reserve(allocated);
        strncat(characters, addend, strlen(addend));
        //characters[allocated] = '\0';
    }

    void string::operator +=(char addend) {
        cout << "Operator += char opened" << endl;
        current_length += 1;
        allocated = current_length + 1;
        reserve(allocated);
        characters[current_length] = addend;
        //characters[allocated] = '\0';
    }

    void string::reserve(size_t n) {
        if(n == allocated or current_length > allocated)
        // Return from func. if size n is the same or size n is less than the current used
            return;

        char *temp;
        allocated = n;
        temp = new char[allocated];
        strncpy(temp, characters, current_length);
        delete [] characters;
        characters = temp;
    }

    string& string::operator =(const string& source) {
        delete [] characters;
        allocated = source.allocated;
        current_length = source.current_length;
        reserve(allocated);
        strncpy(characters, source.characters, source.current_length);
    }

    void string::insert(const string& source, unsigned int position) {
        assert(position <= length());
        reserve(current_length + source.current_length);
        for(int i=current_length-1;i>=position;i--) {
        // Shifts the entries to make room for the source string
            characters[i+source.current_length] = characters[i];
        }

        for(int i=0;i<source.current_length;i++) {
        // Insert the entries before the position index
            characters[i+position] = source.characters[i];
        }
    }

    void string::dlt(unsigned int position, unsigned int num) {
        assert(position + num <= length());
        for(int i=position+num;i<current_length;i++) {
        // Iterate through characters shifting to delete
            characters[i-num] = characters[i];
        }
    } 

    void string::replace(char c, unsigned int position) {
        assert(position < length());
        characters[position] = c;
    }

    void string::replace(const string& source, unsigned int position) {
        assert(position + source.length() <= length());
        for(int i=0;i<source.length();i++) {
        // Iterate through source characters copying to characters
            characters[position+i] = source.characters[i];
        }
    }
    
    // Constant member functions
    char string::operator [] (size_t position) const {
        return characters[position];
    }

    int string::search(char c) const {
        for(int i=0;i<current_length;i++) {
        // Iterate through characters
            if(characters[i] == c)
            // If the character is found, return the first index it is found
                return i;
        }
        // If the character is not found, return -1 as desired
        return -1;
    }

    int string::search(const string& substring) const {
        int flag = 0;
        int j;
        for(int i=0;i<current_length;i++) {
        // Iterate through characters
            for(j=0;j<substring.current_length;j++) {
            // Iterate through substring
                if(characters[i+j] == substring.characters[j])
                // If the characters are the same, continue iterating
                    flag = 1;

                else {
                // If the characters are not the same, break
                    flag = 0;
                    break;        
                }
            }
            if(j==substring.current_length && flag == 1)
            // If the iteration reaches the end of substring and the characters are the same, return the starting index
                return i;
        }
        // If the substring is not found, return -1 as desired
        return -1;
    }

    unsigned int string::count(char c) const {
        int count = 0;
        for(int i=0;i<current_length;i++) {
        // Iterate through characters
            if(characters[i] == c)
            // If the character is the target char., increment count
                count++;
        }
        return 0;
    }
    
    // Friend functions
    std::ostream& operator <<(std::ostream& outs, const string& source) {
        for(int i=0;i<source.current_length;i++) {
        // Iterate through characters
            outs << source.characters[i];
        }
        return outs;
    }
    
    bool operator ==(const string& s1, const string& s2) {
        return strcmp(s1.characters,s2.characters) == 0;
    }

    bool operator !=(const string& s1, const string& s2) {
        return strcmp(s1.characters,s2.characters) != 0;
    }

    bool operator > (const string& s1, const string& s2) {
        return strcmp(s1.characters,s2.characters) > 0;
    }

    bool operator < (const string& s1, const string& s2) {
        return strcmp(s1.characters,s2.characters) < 0;
    }

    bool operator >=(const string& s1, const string& s2) {
        return (s1 > s2) || (s1 == s2);
    }

    bool operator <=(const string& s1, const string& s2) {
        return (s1 < s2) || (s1 == s2);
    }

    // Non-member functions for the string class
    string operator +(const string& s1, const string& s2) {
        cout << "1st Operator + called" << endl;
        string temp;
        temp.reserve(s1.length() + s2.length() + 1);
        cout << "reserve complete" << endl;
        temp += s1;
        cout << "1st added" << endl;
        temp += s2;
        cout << "2nd added" << endl;
        cout << "Operator complete" << endl;
        return temp;
    }

    string operator +(const string& s1, const char addend[ ]) {
        cout << "2nd Operator + called" << endl;
        string temp;
        temp.reserve(s1.length() + strlen(addend));
        temp += s1;
        temp += addend;
        return temp;
    }

    std::istream& operator >> (std::istream& ins, string& target) {
        char *temp = new char[100];
        while(ins && isspace(ins.peek()))
        // Gets rid of the starting white space
            ins.ignore(); 
        ins >> temp;
        target = string(temp);
        return ins;
    }
}