#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>
#include <vector>


class term
{

    char operation;
    std::vector<term> links;
    double value;
    std::string unknownVariable;

    std::vector<std::string> splitString(std::string& str, std::string sepperator)
    {
        std::vector<std::string> result;
        int a = 0;
        for(int i = 0; i + sepperator.length() < str.length(); i++)
        {
            int c = 0;
            for(c = 0; c < sepperator.length(); c++)
            {
                if(str.at(i+c) != sepperator.at(c))
                {
                    break;
                }
                c++;
            }
            if(c == sepperator.length()+1)
            {
                result.push_back(str.substr(a, i));
                a = i + c-1;
            }
        }
        if(a < str.length())
        {
            result.push_back(str.substr(a, str.length()-a));
        }
        return result;
    }

    bool containsOperator(std::string& str, char oper)
    {
        for(int i = 0; i < str.length(); i++)
        {
            //skip inbrackets
            if(str.at(i) == '(')
            {
                int caps = 1;
                i++;
                while (i < str.length() && caps > 0)
                {
                    if(str.at(i) == '(')
                    {
                        caps++;
                    }
                    else if(str.at(i) == ')')
                    {
                        caps--;
                    }
                    i++;
                }
            }
            if(i < str.length())
            {
                if(str.at(i) == oper)
                {
                    if(i > 0)
                    {
                        if(str.at(i-1) == '-' || str.at(i-1) == '+' || str.at(i-1) == '*' || str.at(i-1) == '/' || str.at(i-1) == '^')
                        {
                            i++;
                            continue;
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }

    void load(std::string& termMath)
    {
        char ops[6] = "+-*/^";
        bool isValue = true;

        if(termMath.at(0) == '(' && termMath.at(termMath.length()-1) == ')')
        {
            for(int i = 0; i < termMath.length(); i++)
            {
                if(termMath.at(i) == '(')
                {
                    int first = i;
                    int caps = 1;
                    i++;
                    while (i < termMath.length() && caps > 0)
                    {
                        if(termMath.at(i) == '(')
                        {
                            caps++;
                        }
                        else if(termMath.at(i) == ')')
                        {
                            caps--;
                        }
                        i++;
                    }
                    if(first == 0 && i == termMath.length())
                    {
                        std::string tmp = termMath.substr(1, termMath.length()-2);
                        this->load(tmp);
                        return;
                    }
                }
            }
        }
        


        for(int opi = 0; opi < 5 && termMath.size()>1; opi++)
        {
            if(containsOperator(termMath, ops[opi]) && termMath.at(0)!=ops[opi])
            {
                int a = 0;
                for(int i = 0; i < termMath.length(); i++)
                {
                    //skip inbrackets
                    if(termMath.at(i) == '(')
                    {
                        int caps = 1;
                        i++;
                        while (i < termMath.length() && caps > 0)
                        {
                            if(termMath.at(i) == '(')
                            {
                                caps++;
                            }
                            else if(termMath.at(i) == ')')
                            {
                                caps--;
                            }
                            i++;
                        }
                    }
                    if(i < termMath.length())
                    {
                        if(termMath.at(i) == ops[opi] && i-a > 0)
                        {
                            operation = ops[opi];
                            std::string part = termMath.substr(a,i-a);
                            links.push_back(term(part));
                            a = i + 1;
                        }
                    }
                }
                if(a < termMath.length())
                {
                    operation = ops[opi];
                    std::string part = termMath.substr(a,termMath.length()-a);
                    links.push_back(term(part));
                }
                /*if(links.size() == 1)
                {
                    operation = '#';
                    value = links.at(0).value;
                    if(links.at(0).unknownVariable.size() > 0)
                    {
                        unknownVariable = links.at(0).unknownVariable;
                    }
                    links.clear();
                }*/

                isValue = false;
                break;
            }
        }

        if(isValue)
        {
            operation = '#';
            std::string val = termMath;
            while (val[0] == '(' && val[val.length()-1] == ')')
            {
                val = val.substr(1,val.length()-2);
            }
            setValue(val);
        }
    }

    bool strIsNumeric(std::string& str)
    {
        for(int i = 0; i < str.length(); i++)
        {
            if((str.at(i) < 48 || str.at(i) > 57) && str.at(i) != '.' && str.at(i) != ',' && str.at(i) != '-')
            {
                return false;
            }
        }
        return true;
    }

    unsigned char operationPriority(char operation)
    {
        if(operation == '-' || operation == '+')
        {
            return 0;
        }
        if(operation == '*' || operation == '/')
        {
            return 1;
        }
        if(operation == '^')
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }

    public:

    term()
    {
        operation = '#';
    }

    term(term* other)
    {
        this->operation = other->operation;
        this->unknownVariable = other->unknownVariable;
        this->value = other->value;
        for(int i = 0; i < other->links.size(); i++)
        {
            links.push_back(term(other->links.at(i)));
        }
    }

    void operator= (term& other)
    {
        this->operation = other.operation;
        this->unknownVariable = other.unknownVariable;
        this->value = other.value;
        for(int i = 0; i < other.links.size(); i++)
        {
            links.push_back(term(other.links.at(i)));
        }
    }


    void setValue(std::string numeric)
    {
        value = 0;
        if(strIsNumeric(numeric))
        {
            if(numeric.find('.') != std::string::npos)
            {
                std::vector<std::string> parts = splitString(numeric, ".");
                if(parts.size() == 2)
                {
                    for(int i = 0; i < parts.at(0).length(); i++)
                    {
                        value += (parts.at(0).at(i)-48)*pow(10, parts.at(0).length()-i-1);
                    }
                    for(int i = 0; i < parts.at(1).length(); i++)
                    {
                        value += (parts.at(1).at(i)-48)/pow(10, i+1);
                    }
                }
            }
            else if(numeric.find(',') != std::string::npos)
            {
                std::vector<std::string> parts = splitString(numeric, ",");
                if(parts.size() == 2)
                {
                    for(int i = 0; i < parts.at(0).length(); i++)
                    {
                        value += (parts.at(0).at(i)-48)*pow(10, parts.at(0).length()-i-1);
                    }
                    for(int i = 0; i < parts.at(1).length(); i++)
                    {
                        value += (parts.at(1).at(i)-48)/pow(10, i+1);
                    }
                }
            }
            else
            {
                int start = 0;
                if(numeric.at(0) == '-')
                {
                    start = 1;
                }
                for(int i = start; i < numeric.length(); i++)
                {
                    value += (numeric.at(i)-48)*pow(10, numeric.length()-i-1);
                }
                if(start != 0)
                {
                    value = -value;
                }
            }
        }
        else
        {
            unknownVariable = numeric;
        }
    }

    bool containsUnknownVariables()
    {
        if(unknownVariable.size() > 0)
        {
            return true;
        }
        for(int i = 0; i < this->links.size(); i++)
        {
            if(links.at(i).containsUnknownVariables())
            {
                return true;
            }
        }
        return false;
    }

    bool containsUnknownVariable(std::string& variable)
    {
        if(unknownVariable.size() > 0 && unknownVariable == variable)
        {
            return true;
        }
        for(int i = 0; i < this->links.size(); i++)
        {
            if(links.at(i).containsUnknownVariable(variable))
            {
                return true;
            }
        }
        return false;
    }

    double calculate()
    {
        double result = 0;
        if(operation == '+')
        {
            for(int i = 0; i < links.size(); i++)
            {
                result += links.at(i).calculate();
            }
        }else if(operation == '-')
        {
            result = links.at(0).calculate();
            for(int i = 1; i < links.size(); i++)
            {
                result -= links.at(i).calculate();
            }
        }
        else if(operation == '*')
        {
            result = links.at(0).calculate();
            for(int i = 1; i < links.size(); i++)
            {
                result *= links.at(i).calculate();
            }
        }
        else if(operation == '/')
        {
            result = links.at(0).calculate();
            for(int i = 1; i < links.size(); i++)
            {
                result /= links.at(i).calculate();
            }
        }else if(operation == '^')
        {
            result = links.at(links.size()-1).calculate();
            for(int i = 1; i < links.size(); i++)
            {
                result = pow(links.at(links.size()-i-1).calculate(), result);
            }
        }else
        {
            return value;
        }
        return result;
    }

    std::string toString()
    {
        return this->toString(0);
    }
    std::string toString(unsigned char parentOperationPriority)
    {
        std::string result = "";
        if(operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == '^')
        {
            bool setBracket = false;
            if(parentOperationPriority > operationPriority(operation))
            {
                setBracket = true;
                result = "(";
            }
            for(int i = 0; i < links.size(); i++)
            {
                result += links.at(i).toString(operationPriority(operation));
                if(i < links.size()-1)
                {
                    result += operation;
                }
            }
            if(setBracket)
            {
                result += ")";
            }
        }else
        {
            if(unknownVariable.size() > 0)
            {
                return unknownVariable;
            }
            if(value - (double)((long)value) == 0.0)
            {
                if(value < 0)
                {
                    return "(" + std::to_string((long)value) + ")";  
                }
                return std::to_string((long)value);    
            }
            if(value < 0)
            {
                return "(" + std::to_string(value) + ")";    
            }
            return std::to_string(value);
        }
        return result;
    }

    void derivativeInternal(std::string& variable, char parentOperation)
    {
        if(operation == '*')
        {
            int subc = 0;
            for(int i = 0; i < links.size(); i++)
            {
                if(links.at(i).containsUnknownVariable(variable)) //is a subfunction
                {
                    subc++;
                }
            }
            if(subc == links.size() && links.size() == 2) //Productrule
            {
                term deriOne(links.at(0));
                term one(links.at(0));
                deriOne.derivativeInternal(variable, operation);
                term deriTwo(links.at(1));
                term two(links.at(1));
                deriTwo.derivativeInternal(variable, operation);
                operation = '+';
                links.clear();
                term A;
                A.operation = '*';
                term B;
                B.operation = '*';
                A.links.push_back(deriOne);
                A.links.push_back(two);
                B.links.push_back(deriTwo);
                B.links.push_back(one);
                this->links.push_back(A);
                this->links.push_back(B);
            }
            else if(links.size() == 2 && subc == 1)
            {
                for(int i = 0; i < links.size(); i++)
                {
                    if(links.at(i).containsUnknownVariable(variable)) //is a subfunction
                    {
                        links.at(i).derivativeInternal(variable, operation);
                    }
                }
            }
            
        }
        else if(operation == '+' || operation == '-')
        {
            for(int i = 0; i < links.size(); i++)
            {
                links.at(i).derivativeInternal(variable, operation);
            }
        }
        else if(operation == '/')
        {

        }
        else if(operation == '^')
        {
            int subc = 0;
            for(int i = 0; i < links.size(); i++)
            {
                if(links.at(i).containsUnknownVariable(variable)) //is a subfunction
                {
                    subc++;
                }
            }
            if(links.size() == 2 && subc == 1)
            {
                if(links.at(0).containsUnknownVariable(variable)) // x^n
                {
                    term n(links.at(1));
                    term x(this);
                    x.links.at(1).value -= 1;
                    operation = '*';
                    links.clear();
                    links.push_back(n);
                    links.push_back(x);
                }
                else if(links.at(1).containsUnknownVariable(variable) && (long)((links.at(0).value - M_E) * 10000) == 0)
                {
                    term h(links.at(1));
                    term g(this);
                    operation = '*';
                    links.clear();
                    links.push_back(g);
                    h.derivativeInternal(variable, operation);
                    links.push_back(h);
                }
            }
        }
        else
        {
            if(unknownVariable.size()>0)
            {
                if(unknownVariable == variable)
                {
                    value = 1.0;
                }
                else
                {
                    value = 0.0;
                }
            }
            else
            {
                value = 0.0;
            }
        }
    }

    term derivative(std::string variable)
    {
        term result(this);
        result.derivativeInternal(variable, operation);
        int dbg = 0;
        return result;
    }

    term(std::string& termMath)
    {
        this->load(termMath);
    }

};




int main(int args, char** arg)
{


    std::string termStr = "(8-7,3415)+(((4.6456+6)/2)*2)^3";//"(a-b)+((a+c)/d)*e^f";

    std::string easy = "5*(7-3-2)^2";

    std::string function1 = "0.5*x^3+3*x^2-5.764*x+123,1415";

    std::string function2 = "(7*x^2+1)*" + std::to_string(M_E) + "^((-2)*x)";

    term t1(function2);

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
        term t1_D1 = t1.derivative(std::string("x"));
        printf("Derivate of %s --> %s\n", t1.toString().c_str(), t1_D1.toString().c_str());
    }
    

    int dbg = 1;

    return 0;
}

