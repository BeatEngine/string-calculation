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
                    return true;
                }
            }
        }
        return false;
    }

    void load(std::string& termMath)
    {
        char ops[6] = "-+*/^";
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
        


        for(int opi = 0; opi < 5; opi++)
        {
            if(containsOperator(termMath, ops[opi]))
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
                        if(termMath.at(i) == ops[opi])
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
            if((str.at(i) < 48 || str.at(i) > 57) && str.at(i) != '.' && str.at(i) != ',')
            {
                return false;
            }
        }
        return true;
    }

    public:

    term()
    {
        operation = '#';
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
                for(int i = 0; i < numeric.length(); i++)
                {
                    value += (numeric.at(i)-48)*pow(10, numeric.length()-i-1);
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

/*
    if(termMath.at(i) == '(')
    {
        int caps = 0;
        int a = i;
        std::string subTerm;
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
        subTerm = termMath.substr(a, i-a);

    }
*/

    term(std::string& termMath)
    {
        this->load(termMath);
    }

};




int main(int args, char** arg)
{


    std::string termStr = "(8-7,3415)+(((4.6456+6)/2)*2)^3";//"(a-b)+((a+c)/d)*e^f";

    std::string easy = "5*(7-3-2)^2";

    term t1(termStr);

    bool containsUnknowns = t1.containsUnknownVariables();

    printf("Contains unknowns: %d\n", containsUnknowns);

    if(!containsUnknowns)
    {
        printf("Calulated result %s = %f\n", termStr.c_str(), t1.calculate());
    }

    int dbg = 1;

    return 0;
}

