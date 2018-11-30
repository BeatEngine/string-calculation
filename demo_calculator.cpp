#include "strcalculation.h"



int main()
{
    printf("Usage:\n");
    printf("'+' for addition!\n");
    printf("'-' for subtraction!\n");
    printf("'*' for multiplication!\n");
    printf("'/' for division!\n");
    printf("'^' for exponential power (and roots if you know)!\n");

    char tmp[500];
    std::string term;
    while(1)
    {
        printf("Term:");
        gets(tmp);
        term = tmp;
        strcalc::calc_contain test;
        test.load(term);
        printf("\nLoaded Term '%s'\n\n",term.c_str());
        printf("Result:%s=%lf\n",tmp,test.calculate());


        printf("\n");

    }





    return 0;
}









