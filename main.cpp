#include "strcalculation.h"












int main()
{

    strcalc::calc_contain test;
    std::string term = "(50-20*3^(4-1))/(1+2.7^5)";//"1+2+3*-(-4-2*-3)+-6";
    test.load(term);
    double result = test.calculate();
    printf("Term:'%s'\n",term.c_str());
    printf("= %f\n",result);

    return 0;
}









