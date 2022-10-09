#include <iostream>
#include "keyed_bag.h"
#include <cassert>
#include <cmath>

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
    keyed_bag::keyed_bag() {
        bag_count = 0;
    }

    void keyed_bag::erase() {
        //run through arrays and remove all values
        for(int i = bag_count; i > 0; i--) {
            keys[i] = '\0';
            data[i] = '\0';
        }
        //there is nothing in the bag
        bag_count = 0;
    }

    bool keyed_bag::erase(const key_type& key)  {
        //search if the term you want erased exists
        for(int i = 0; i < bag_count; i++) {
            //if there is a matching key
            if(keys[i] == key) {
                //shift all keys after deletion left 1
                for(int j = i; j < bag_count; j++) {
                    keys[j] = keys[j+1];
                    data[j] = data[j+1];
                }
                //deleted value and shifted, so return true
                bag_count--;
                return true;
            }
        }
        //value not found so return false
        return false;
    }

    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert(size() < CAPACITY);
        //precondition of not already being in bag
        assert(has_key(key) == false);
        //insert into array
        keys[bag_count] = key;
        data[bag_count] = entry;
        bag_count++;
    }

    void keyed_bag::operator +=(const keyed_bag& addend) {
        //confirm preconditions
        assert(size() + addend.size() <= CAPACITY);
        assert(hasDuplicateKey(addend) == false);
        //loop through array + 2nd array length
        for(int i = 0; i < addend.size(); i++) {
            //insert values into back of array
            keys[bag_count] = addend.keys[i];
            data[bag_count] = addend.data[i];
            bag_count++;
        }
    }

    bool keyed_bag::has_key(const key_type& key) const {
        //loop through array
        for(int i = 0; i < bag_count; i++) {
            //if there is a duplicate key return true
            if(keys[i] == key) {
                return true;
            }
        }
        //no duplicates return false
        return false;
    }

    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key) == true);
        //loop through array
        for(int i = 0; i < bag_count; i++) {
            //when key is found return data value
            if(keys[i] == key) {
                return data[i];
            }
        }
    }

    keyed_bag::size_type keyed_bag::size() const {
        //return size of arrays
        return bag_count;
    }

    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        //variable to hold how many times it appears
        int count = 0;
        //loop through array
        for(int i = 0; i < bag_count; i++) {
            //when you find data that matches the target increment
            if(data[i] == target) {
                count++;
            }
        }
        //return amount of targets in array
        return count;
    }

    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        //loops through original bag keys
        for(int i = 0; i < bag_count; i++) {
            //loops through other bag keys
            for(int j = 0; j < otherBag.size(); j++) {
                //if keys of both bags match return true
                if(keys[i] == otherBag.keys[j]) {
                    return true;
                }
            }
        }
        //no duplicate keys between bags
        return false;
    }

    keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
        //confirm preconditions
        assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
        assert(b1.hasDuplicateKey(b2) == false);
        //use previous operator to add bags together
        keyed_bag combined;
        combined += b1;
        combined += b2;
        //return combined bag
        return combined; 
    }

}