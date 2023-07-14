#include <iostream>
#include <math.h>
using namespace std;

// inspired from  -  https://www.youtube.com/watch?v=HEfHFsfGXjs

const int PI_DIGITS = 10;

int main () {
    // starting positions -> m2 is kept in left of m1,  m1 approaches m2 with unit velocity 
    // initial masses of blocks
    long long int m2 = 1, m1 = pow(100, PI_DIGITS - 1);
    // initial velocities of blocks, right is taken as +ve direction
    long double v1 = -1, v2 = 0;
    int number_of_collisions = 0;
    while (!(v1 > v2 && v1 > 0)) {
        if ((v2 > v1 && v1 < 0) || (v1 < v2 && v2 > 0)) {
            number_of_collisions++;
            double vf1 = ((m1 - m2)*v1 + 2*m2*v2)/(m1 + m2);
            double vf2 = ((m2 - m1)*v2 + 2*m1*v1)/(m1 + m2);
            v1 = vf1;
            v2 = vf2;
        }
        if (v2 < 0) {
            number_of_collisions++; // collision with wall
            v2 *= -1; // changes direction considering wall with infinite weight.
        }
    }
    cout << number_of_collisions << endl;
    return 0;
}