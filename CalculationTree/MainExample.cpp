#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
#include <vector>

#include "mathematicalTerm.h"

std::vector<double> findNullsOf(term& function, term& functionDerivative)
{
    std::vector<double> results;
    std::string x = "x";
    double r;


    r = 1;    
    for(int i = 0; i < 15; i++)
    {
        r = r - function.calculate(x, r)/functionDerivative.calculate(x, r);
    }

    if((long)(function.calculate(x, r)*10) == 0)
    {
        results.push_back(r);
    }

    r = -1;    
    for(int i = 0; i < 15; i++)
    {
        r = r - function.calculate(x, r)/functionDerivative.calculate(x, r);
    }

    if((long)(function.calculate(x, r)*10) == 0)
    {
        results.push_back(r);
    }

    r = 50;    
    for(int i = 0; i < 15; i++)
    {
        r = r - function.calculate(x, r)/functionDerivative.calculate(x, r);
    }

    if((long)(function.calculate(x, r)*10) == 0)
    {
        results.push_back(r);
    }

    r = -50;
    double a;
    double b;
    for(int i = 0; i < 15; i++)
    {
        a = function.calculate(x, r);
        b = functionDerivative.calculate(x, r);
        r -= a/b;
    }

    if((long)(function.calculate(x, r)*10) == 0)
    {
        results.push_back(r);
    }


    for(int i = 1; i < results.size(); i++)
    {
        if((long)(results.at(i-1)*1000 - results.at(i)*1000) == 0)
        {
            results.erase(results.begin() + i);
            i = 0;
        }
    }

    return results;
}


void functionInfo(std::string function)
{
    std::string x = "x";
    term f(function);
    printf("f(x) = %s\n", f.toString().c_str());
    term f1 = f.derivative(x);
    printf("f'(x) = %s\n", f1.toString().c_str());
    term f2 = f1.derivative(x);
    printf("f''(x) = %s\n", f2.toString().c_str());
    term f3 = f2.derivative(x);
    printf("f'''(x) = %s\n", f3.toString().c_str());

    std::vector<double> nulls = findNullsOf(f, f1);
    printf("\nZeros of the function:\n");
    if(nulls.size() == 0)
    {
        printf("f(x) = 0 --> x = {}\n");
    }
    else if (nulls.size() == 1)
    {
        printf("f(x) = 0 --> x = %f\n", nulls.at(0));
    }
    else
    {
        printf("f(x) = 0 --> x = {");
        for(int i = 0; i < nulls.size(); i++)
        {
            printf("%f", nulls.at(i));
            if(i < nulls.size()-1)
            {
                printf(", ");
            }
        }
        printf("}\n");
    }
    std::vector<double> nulls1 = findNullsOf(f1, f2);
    if(nulls1.size() == 0)
    {
        printf("f'(x) = 0 --> x = {}\n");
    }
    else if (nulls1.size() == 1)
    {
        printf("f'(x) = 0 --> x = %f\n", nulls1.at(0));
    }
    else
    {
        printf("f'(x) = 0 --> x = {");
        for(int i = 0; i < nulls1.size(); i++)
        {
            printf("%f", nulls1.at(i));
            if(i < nulls1.size()-1)
            {
                printf(", ");
            }
        }
        printf("}\n");
    }
    if(nulls1.size() > 0)
    {
        printf("\nExtremas:\n");
        long attribute;
        for(int i = 0; i < nulls1.size(); i++)
        {
            attribute = (long)(f2.calculate(x, nulls1.at(i)) * 1000);
            if(attribute < 0)
            {
                printf("Maxima     : f(x)       --> {x = %f, f(x) = %f}\n", nulls1.at(i), f.calculate(x, nulls1.at(i)));
                printf(" Conditions: f'(x) = 0  --> {x = %f, f'(x) = %f}\n", nulls1.at(i), f1.calculate(x, nulls1.at(i)));
                printf(" Conditions: f''(x) > 0 --> {x = %f, f''(x) = %f}\n", nulls1.at(i), f2.calculate(x, nulls1.at(i)));
            }
            else if (attribute > 0)
            {
                printf("Minima     : f(x)       --> {x = %f, f(x) = %f}\n", nulls1.at(i), f.calculate(x, nulls1.at(i)));
                printf(" Conditions: f'(x) = 0  --> {x = %f, f'(x) = %f}\n", nulls1.at(i), f1.calculate(x, nulls1.at(i)));
                printf(" Conditions: f''(x) > 0 --> {x = %f, f''(x) = %f}\n", nulls1.at(i), f2.calculate(x, nulls1.at(i)));
            }
            else if(f3.calculate(x, nulls1.at(i)) != 0)
            {
                printf("Saddle Point : f(x) --> {x = %f, f(x) = %f}\n", nulls1.at(i), f.calculate(x, nulls1.at(i)));
                printf(" Conditions: f'(x) = 0  --> {x = %f, f'(x) = %f}\n", nulls1.at(i), f1.calculate(x, nulls1.at(i)));
                printf(" Conditions: f''(x) = 0 --> {x = %f, f''(x) = %f}\n", nulls1.at(i), f2.calculate(x, nulls1.at(i)));
            }
        }
    }
    std::vector<double> nulls2 = findNullsOf(f2, f3);
    
    if(nulls2.size() > 0)
    {
        printf("\nInflection points:\n");
        double attribute;
        for(int i = 0; i < nulls2.size(); i++)
        {
            attribute = f3.calculate(x, nulls2.at(i));
            if(attribute != 0)
            {
                printf("Inflection point: f(x)       --> {x = %f, f(x) = %f}\n", nulls2.at(i), f.calculate(x, nulls2.at(i)));
                printf(" Conditions     : f''(x) = 0  --> {x = %f, f'(x) = %f}\n", nulls2.at(i), f2.calculate(x, nulls2.at(i)));
                printf(" Conditions     : f'''(x) ≠ 0 --> {x = %f, f''(x) = %f}\n", nulls2.at(i), f3.calculate(x, nulls2.at(i)));
            }
        }
    }

}



int main(int args, char** arg)
{


    std::string termStr = "(8-7,3415)+(((4.6456+6)/2)*2)^3";//"(a-b)+((a+c)/d)*e^f";

    std::string easy = "5*(7-3-2)^2";

    std::string function1 = "0.5*x^3+3*x^2-5.764*x+123,1415";

    std::string function2 = "(7*x^2+1)*" + std::to_string(M_E) + "^((-2)*x)";

    std::string function3 = "(a*x^b+c)*" + std::to_string(M_E) + "^(d*x)";

    term t1(function2);

    term t2(function1);

    term t3(function3);

    bool containsUnknowns = t1.containsUnknownVariables();

    printf("Contains unknowns: %d\n", containsUnknowns);

    std::string generated = t1.toString();

    term tCheck(generated);

    if(!containsUnknowns)
    {
        printf("Calulated result %s = %s = %f\n",termStr.c_str(), generated.c_str(), t1.calculate());
        printf("Check generated: %f == %f ? --> %d",t1.calculate(), tCheck.calculate(), tCheck.calculate() == t1.calculate());
    }
    else
    {
        functionInfo(function1);
        printf("\n");
        functionInfo(function2);
        printf("\n");
        functionInfo(function3);
        printf("\n");
    }

    int dbg = 1;

    return 0;
}

