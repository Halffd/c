#include <iostream>
#include <chrono>

#include "Reel.h"

using namespace std;
using namespace std::chrono;

using DType = unsigned short;
using LongDouble = Reel<DType, 420u / sizeof (DType)>;

LongDouble arctan(LongDouble x ) {

    if(abs(x) > LongDouble(1.L))
        throw "arctan(x) only works for -1 <= x <= 1";

    // compute arctan(x) as x - x^3/3 + x^5/5 - x^7/7 + ..., which is valid for -1 <= x <= 1 (i.e. angles between
    // -PI/4 and PI/4). It converges faster when x is closer to 0.

    LongDouble result;
    LongDouble num = x;
    LongDouble denum = 1;
    LongDouble x2 = x * x;
    LongDouble two = 2.L;

    LongDouble epsilon = pow( LongDouble(2.L) , LongDouble::digits );
    epsilon = LongDouble(1.L) / epsilon;

    LongDouble ratio = num / denum;
    result += ratio;

    while( abs( ratio / result ) > epsilon) {
        num *= -x2;
        denum += two;
        ratio = num / denum;
        result += ratio;
    }
    cout << endl;
    return result;
}

int main() {
    cout << "Precision : " << LongDouble::digits << " bits" << endl;

    // Compute PI using https://en.wikipedia.org/wiki/John_Machin#Formula

    auto start = system_clock::now();

    LongDouble d1 = LongDouble(1.L) / LongDouble (5.L);
    LongDouble d2 = LongDouble(1.L) / LongDouble (239.L);
    LongDouble ad1 = arctan( d1 );
    LongDouble ad2 = arctan( d2 );

    auto pi = LongDouble(16.L) * ad1  - LongDouble(4.L) * ad2;

    auto finish = system_clock::now();

    cout << setprecision(1000) << "PI = " << pi << endl;

    auto finish_display = system_clock::now();

    cout << "Computed in  " << duration_cast<milliseconds>(finish - start).count() << " ms" << endl;
    cout << "Displayed in " << duration_cast<milliseconds>(finish_display - finish).count() << " ms" << endl;

    return 0;

    LongDouble const PI( HARD CODE PI HERE WITH 1000 DIGITS OF PRECISION TO CHECK RESULT )

    cout << "Error : " << pi - PI << endl;
}