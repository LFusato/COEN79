#include "sequence1.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {
    //constructor
    sequence::sequence() {
        data[CAPACITY] = 0;
        used = 0;
        current_index = 0;
    }

    void sequence::start() {
        //move to first index
        current_index = 0;
    }

    void sequence::end() {
        //move to last index
        current_index = used - 1;
    }

    void sequence::last() {
        //move to the last point in array
        current_index = CAPACITY - 1;
    }

    void sequence::advance() {
        assert(is_item() == true);
        //if valid, increment index
        if(current_index < used) {
            current_index++;
        }
    }

    void sequence::retreat() {
        //decrement index
        if(current_index > 0) {
            current_index--;
        }
    }

    void sequence::insert(const value_type& entry) {
        assert(size() < CAPACITY);
        //execute when the list is empty
        if (used == 0) {
            //insert into first spot
            data[0] = entry;
            current_index = 0;
        }
        //execute when at least one item is in list
        else {
            //for loop to shift values, must decrement to avoid loss of data
            for(int i = used; i > current_index; i--) {
                data[i] = data[i-1];
            }
            //insert new item into empty spot
            data[current_index] = entry;
        }
        //increment size
        used++;
    }

    void sequence::attach(const value_type& entry) {
        assert(size() < CAPACITY);
        //execute when the list is empty
        if(used == 0) {
            data[0] = entry;
            current_index = 0;
        }
        //execute if there is at least one item in array
        else {
            //loop to shift values after current, decrement to avoid data loss
            for(int i = used; i > current_index + 1; i--) {
                data[i] = data[i-1];
            }
            //insert new item into spot after current
            data[current_index+1] = entry;
            //change current to new spot
            current_index++;
        }
        //increment size
        used++;
    }

    void sequence::remove_current() {
        assert(is_item() == true);
        //removes current item in array by replacement
        for(int i = current_index; i < used; i++) {
            data[i] = data[i+1];
        }
        //decrement size
        used--;
    }

    void sequence::insert_front(const value_type& entry) {
        assert(size() < CAPACITY);
        //moves current to front of array
        current_index = 0;
        //calls insert to add value and increment size
        insert(entry);
    }

    void sequence::attach_back(const value_type& entry) {
        assert(size() < CAPACITY);
        //move current to end of array
        current_index = used - 1;
        //calls attach to add value and increment size
        attach(entry);
    }

    void sequence::remove_front() {
        assert(is_item() == true);
        //move current to front of array
        current_index = 0;
        //calls remove and decrements size
        remove_current();
    }

    void sequence::operator +=(const sequence&rhs) {
        //marker to iterate through rhs
        int rhsindex = 0;
        //concatenate btoh sequences
        for(int i = used; i < used + rhs.used; i++) {
            data[i] = rhs.data[rhsindex];
            rhsindex++;
        }
        //new array is size of both arrays combined
        used = used + rhs.used;
    }

    sequence::size_type sequence::size() const {
        //return size value
        return used;
    }

    bool sequence::is_item() const {
        //if the current_index is at an index within the size contraints
        //there is a valid item in the array
        if (current_index < used) {
            return true;
        }
        //if there is no item in the array
        else {
            return false;
        }
    }

    sequence::value_type sequence::current() const {
        assert(is_item() == true);
        //returns value held in array at current_index
        return data[current_index];
    }

    sequence::value_type sequence::operator[](int index) const {
        assert(index < used);
        return data[index];
    }

    double sequence::mean() const {
        //variable to hold sum
        sequence::value_type total = 0;
        //iterate through array, adding up all values
        for(int i = 0; i < used; i++) {
            total = total + data[i];
        }
        //reutrn average
        return total/used;
    }

    double sequence::standardDeviation() const {
        //variable to hold total
        sequence::value_type total = 0;
        //iterates through array, summing the (data value - mean)^2
        for(int i = 0; i < used; i++) {
            total = total + pow(data[i] - mean(), 2);
        }
        //return standard deviation
        return sqrt(total/used);
    }

    sequence operator +(const sequence& lhs, const sequence& rhs) {
        //create combined object
        sequence combined;
        //copy lhs to combined array
        combined += lhs;
        //copy rhs to combined array, values after lhs
        combined += rhs;

        return combined;
    }

    sequence::value_type summation(const sequence &s) {
        //create sum variable
        sequence::value_type sum;
        //loop through array, adding values
        for(int i = 0; i < s.size(); i++) {
            sum = sum + s[i];
        }
        return sum;
    }

}