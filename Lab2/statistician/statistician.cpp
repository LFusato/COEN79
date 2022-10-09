// FILE: statistician.cpp
// CLASS IMPLEMENTED: statistician (see stats.h for documentation)

#include <cassert>   // Provides assert
#include <iostream>  // Provides istream class
#include "statistician.h"

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{
    //constructor initialization
    statistician::statistician(){
        total = 0;
        size = 0;
    }

    //next function
    void statistician::next(double r) {
        //add number to total
        total = total + r;
        //increase number of values held by 1
        size++;

        //to figure out minimum and maximum
        //when there is only 1 value after next
        if(size == 1) {
            min = r;
            max = r;
        //more than 1 value    
        } else {
            //value is smaller than min
            if(r < min) {
                min = r;
            //value is larger than max    
            } else if (r > max) {
                max = r;
            }
        }
        
    }

    //reset function
    void statistician::reset() {
        total = 0;
        size = 0;

        return;
    }

    //size function
    int statistician::length() const {
        return size;
    }

    //total value function
    double statistician::sum() const {
        return total;
    }

    //average function
    double statistician::mean() const {
        //check precondition
        assert(length() > 0);
        //return mean
        return total/size;
    }

    //minimum function
    double statistician::minimum() const {
        //check procondition
        assert(length() > 0);
        return min;
    }

    //maximum function
    double statistician::maximum() const {
        //check precondition
        assert(length() > 0);
        return max;
    }

    //add operator function
    statistician operator +(const statistician& s1, const statistician& s2) {
        //create placeholder object
        statistician combined;
        //add sums together
        combined.total = s1.sum() + s2.sum();
        //add lengths together
        combined.size = s1.length() + s2.length();
        //pick the smallest minimum between 2 objects
        if(s1.minimum() < s2.minimum()) {
            combined.min = s1.minimum();
        } else {
            combined.min = s2.minimum();
        }
        //pick the largest maximum between 2 objects
        if(s1.maximum() > s2.maximum()) {
            combined.max = s1.maximum();
        } else {
            combined.max = s2.maximum();
        }

        //calcualte combined mean
        combined.avg = combined.sum()/combined.length();

        //return combined object
        return combined;
    }
    
    //multiply operator function
    statistician operator *(double scale, const statistician& s) {
        //create placeholder object
        statistician scaled;
        //multiply object sum and size by value
        scaled.total = scale * s.sum();
        scaled.size = scale * s.length();
        //size cannot be negative so adjust if so
        if (scaled.size < 0) {
            scaled.size = -scaled.size;
        }
        //minimum and max values are switched upon multiplication by a negative, so fix accordingly
        if(scale > 0) {
            scaled.min = scale * s.minimum();
            scaled.max = scale * s.maximum();
        } else {
            scaled.min = scale * s.maximum();
            scaled.max = scale * s.minimum();
        }
        
        //calculate object mean
        scaled.avg = scaled.sum()/scaled.length();

        return scaled;
    }
    //equal operator function
    bool operator ==(const statistician& s1, const statistician& s2) {
        //return true if both are empty or exactly the same
        if ((s1.length() == 0 && s2.length() == 0) ||
            ((s1.length() == s2.length()) && 
             (s1.sum() == s2.sum()) &&
             (s1.mean() == s2.mean()) &&
             (s1.minimum() == s2.minimum()) &&
             (s1.maximum() == s2.maximum()))) {
            return true;
        } else {
            return false;
        }
    }
}




