#include <iostream>
using namespace std;

class box {
    public:
        box(double l =2.0, double b = 2.0, double h = 2.0) {
            length = l;
            breadth = b;
            height = h;

            boxNum++;
            cout << "Num " << boxNum << endl;
        }

        double volume() {
            return length * breadth * height;
        }

    private:
        double length;
        double breadth;
        double height;
        static int boxNum;
};

int box::boxNum = 0;

int main(void) {
    box Box1(3.3,1.2,1.5);

    box Box2(8.5,6.0,2.0);

    return 0;
}