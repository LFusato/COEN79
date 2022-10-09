#include "random.h"
#include <iostream>

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2 {
    //constructor initialization
    rand_gen::rand_gen(int seedInput, int multiplierInput, int incrementInput, int modulusInput) {
        seed = seedInput;
        multiplier = multiplierInput;
        increment = incrementInput;
        modulus = modulusInput;
    }
    //set seed function
    void rand_gen::set_seed(int newSeed) {
        seed = newSeed;
    }
    //next seed function
    int rand_gen::next() {
        //seed equation, build upon past seed equations conducted
        seed = (multiplier * seed + increment) % modulus;

        return seed;
    }
    //print values function
    void rand_gen::print_info() {
        cout << "Seed: " << seed << endl;
        cout << "Multiplier: " << multiplier << endl;
        cout << "Increment: " << increment << endl;
        cout << "Modulus: " << modulus << endl;
    }
}