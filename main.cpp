#include "strcalculation.h"












int main()
{

    strcalc::calc_contain test;
    std::string term = "1+2+3*-(-4-2*-3)+-6";
    test.load(term);
    double result = test.calculate();
    printf("Result:%f\n",result);

    test.~calc_contain();
    return 0;
}









