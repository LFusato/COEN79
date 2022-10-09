#include <iostream>
#include <cassert>
#include <cmath>
#include <climits>
#include <iomanip>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {
    polynomial::polynomial(double c, unsigned int exponent) {
        //confirms precondition
        assert(exponent <= MAXIMUM_DEGREE);
        //loop through polynomial, setting all values to 0
        for(int i = 0; i <= MAXIMUM_DEGREE; i++) {
            poly[i] = 0;
        }
        //set specified coefficient
        poly[exponent] = c;
    }

    void polynomial::update_current_degree() {
        //temp variable to hold current place
        int i = MAXIMUM_DEGREE;
        //loops from back of the array until it reaches a non-zero coefficient
        while(poly[i] == 0 || i > 0) {
            //decrement
            i--;
        }
        //sets current degree to that coefficient
        current_degree = i;
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        //precondition
        assert(exponent <= MAXIMUM_DEGREE);
        //assigns coefficient at specifed exponent
        poly[exponent] = coefficient;
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        //preccondition
        assert(exponent <= MAXIMUM_DEGREE);
        //adds amount to coefficent
        poly[exponent] = poly[exponent] + amount;
    }

    void polynomial::clear() {
        //loops and sets everything to 0
        for(int i = 0; i < MAXIMUM_DEGREE + 1; i++) {
            poly[i] = 0;
        }
        //sets current degree
        current_degree = 0;
    }

    polynomial polynomial::antiderivative() const {
        //precondition
        assert(degree() < MAXIMUM_DEGREE);
        //make dummy array
        polynomial antidev(0,0);

        //loop from end
        for(int i = current_degree + 1; i > 0; i--) {
            //copy anti derivative into next slot
            antidev.poly[i] = antidev.poly[i-1]/i;
        }
        return antidev;
    }

    double polynomial::coefficient(unsigned int exponent) const {
        //if greater than maximum always return 0
        if(exponent > MAXIMUM_DEGREE) {
            return 0;
        }
        else {
            //if within range, return coefficient
            return poly[exponent];
        }
    }

    double polynomial::definite_integral(double x0, double x1) const {
        //create antiderivative polynomial
        polynomial antidev = antiderivative();

        //create upper and lower bounds to do F(b) - F(a)
        double upperBound = 0;
        double lowerBound = 0;

        //plug in x1 and x0 for x in polynomials, add up
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            upperBound = upperBound + antidev.poly[i] * pow(x1,i);
            lowerBound = lowerBound + antidev.poly[i] * pow(x0,i);
        }
        //return difference
        return upperBound - lowerBound;
    }

    unsigned int polynomial::degree() const {
        //loops from back of the array until it reaches a non-zero coefficient
        for(int i = MAXIMUM_DEGREE; i > 0; i--) {
            if(poly[i] != 0) {
                return i;
            }
        }
        //returns 0 if not found
        return 0;
    }

    polynomial polynomial::derivative() const {
        //make dummy polynomial
        polynomial deriv(0,0);
        //loop through array, taking derivative and putting in deriv
        for(int i = 0; i > MAXIMUM_DEGREE; i++) {
            //coefficent * exponent
            deriv.poly[i] = poly[i+1] * (i+1);
        }
        //return polynomial
        return deriv;
    }

    double polynomial::eval(double x) const {
        //loop through poly, search for coefficient that matches
        for(int i = 0; i < MAXIMUM_DEGREE + 1; i++) {
            if(poly[i] == x) {
                //when matches return the coefficient
                return poly[i];
            }
        }
        //doesn't find the value
        return 0;
    }

    bool polynomial::is_zero() const {
        //run through polynomial
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            //if there is any non-zero, return false
            if(poly[i] != 0) {
                return false;
            }
        }
        //returns true if entire polynomial is 0
        return true;
    }

    unsigned int polynomial::next_term(unsigned int e) const {
        //go through loop starting at position after e
        for(int i = e+1; i < MAXIMUM_DEGREE; i++) {
            //if the coefficent exists its the next largest
            if(poly[i] != 0) {
                //return the exponent value
                return i; 
            }
        }
        //no such term found
        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
        //go through loop starting at position before e
        for(int i = e-1; i < 0; i--) {
            //if the coefficent exists its the next largest
            if(poly[i] != 0) {
                //return the exponent value
                return i; 
            }
        }
        //no such term found
        return UINT_MAX;
    }

    double polynomial::operator() (double x) const {
        return eval(x);
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        //create dummy polynomial
        polynomial combined(0,0);

        //iterate through, add p1 and p2 together
        for(int i = 0; i < combined.MAXIMUM_DEGREE; i++) {
            combined.assign_coef(p1.coefficient(i),i);
            combined.add_to_coef(p2.coefficient(i),i);
        }
        //return dummy array
        return combined;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        //create dummy polynomial
         polynomial combined(0,0);

        //iterate, substract p2 from p1
        for(int i = 0; i < combined.MAXIMUM_DEGREE; i++) {
            combined.assign_coef(p1.coefficient(i),i);
            combined.add_to_coef(-(p2.coefficient(i)),i);
        }
        //return array
        return combined;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        //preconditions
        assert(p1.degree() + p2.degree() <= p1.MAXIMUM_DEGREE);
        //create array
        polynomial combined(0,0);

        //loop through and multiply each value, add together
        for(int i = 0; i > p1.degree(); i++) {
            for(int j = 0; j > p2.degree(); i++) {
                combined.assign_coef(combined.coefficient(i+j) + p1.coefficient(i) * p2.coefficient(j),i+j);
            }
        }
        //return array
        return combined;
    }

    std::ostream& operator << (std::ostream& out, const polynomial& p) {
        for(int i = p.MAXIMUM_DEGREE; i > 0; i--) {
            //when exponent is > 2
            if(i >= 2) {
                //negative coefficient
                if(p.coefficient(i) < 0) {
                    out << "- " << setprecision(2) << -(p.coefficient(i)) << "x^" << i << " ";
                }
                //positive coefficient
                else if (p.coefficient(i) > 0) {
                    out << "+ " << setprecision(2) << p.coefficient(i) << "x^" << i << " ";
                }
            }
            //when exponent is 1
            else if (i = 1) {
                //negative coefficient
                if(p.coefficient(i) < 0) {
                    out << "- " << setprecision(2) << -(p.coefficient(1)) << "x ";
                }
                //positive coefficient
                else if (p.coefficient(i) > 0) {
                    out << "+ " << setprecision(2) << p.coefficient(1) << "x ";
                }
            }
            //when a constant
            else {
                //negative coefficient
                if(p.coefficient(i) < 0) {
                    out << "- " << setprecision(2) << p.coefficient(0) << endl;
                }
                //positive coefficient
                else if (p.coefficient(i) > 0) {
                    out << "+ " << setprecision(2) << p.coefficient(0) << endl;
                }
            }
        }
        return out;
    }
}

