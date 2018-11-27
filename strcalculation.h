#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>

#include <math.h>

namespace strcalc
{


void printstrvec(std::vector<std::string>& obj)
{
    long i;
    for(i=0;i<obj.size();i++)
    {
        printf("%s;",obj.at(i).c_str());
    }
    printf("\n");
}
void printstrvec(std::vector<char>& obj)
{
    long i;
    for(i=0;i<obj.size();i++)
    {
        printf("%c;",obj.at(i));
    }
    printf("\n");
}

void intervalstrcopy(std::string& source, std::string& destination, long a,long b)
{

if(a>=0&&a<=b&&b<source.size())
{
    destination = "";
    while(a<=b)
    {
        destination+=source.at(a);
        a++;
    }
}
else
{
    printf("str-copy interval error!\n");
}

}

void str_pow(std::string& a,std::string& b)
{
    double ad = 0;
    double bd = 0;
    sscanf(a.c_str(),"%lf",&ad);
    sscanf(b.c_str(),"%lf",&bd);
    char tmp[10];
    memset(tmp,0,10);
    sprintf(tmp,"%lf",pow(ad,bd));
    a = "";
    a+= tmp;
}
void str_mul(std::string& a,std::string& b)
{
    double ad = 0;
    double bd = 0;
    sscanf(a.c_str(),"%lf",&ad);
    sscanf(b.c_str(),"%lf",&bd);
    char tmp[10];
    memset(tmp,0,10);
    sprintf(tmp,"%lf",ad*bd);
    a = "";
    a+= tmp;
}
void str_div(std::string& a,std::string& b)
{
    double ad = 0;
    double bd = 0;
    sscanf(a.c_str(),"%lf",&ad);
    sscanf(b.c_str(),"%lf",&bd);
    char tmp[10];
    memset(tmp,0,10);
    sprintf(tmp,"%lf",ad/bd);
    a = "";
    a+= tmp;
}
void str_add(std::string& a,std::string& b)
{
    double ad = 0;
    double bd = 0;
    sscanf(a.c_str(),"%lf",&ad);
    sscanf(b.c_str(),"%lf",&bd);
    char tmp[10];
    memset(tmp,0,10);
    sprintf(tmp,"%lf",ad+bd);
    a = "";
    a+= tmp;
}
void str_sub(std::string& a,std::string& b)
{
    double ad = 0;
    double bd = 0;
    sscanf(a.c_str(),"%lf",&ad);
    sscanf(b.c_str(),"%lf",&bd);
    char tmp[10];
    memset(tmp,0,10);
    sprintf(tmp,"%lf",ad-bd);
    a = "";
    a+= tmp;
}

void str_term_calc(std::string& input, std::string& output)
{
    std::vector<std::string> numbers;
    std::vector<char> operators;
    //DEBUG
    //printf("c_inp:%s\n",input.c_str());
    bool negation = 0;
    std::string tmp;
    long i = 0;
    for(i=0;i<input.size();i++)//extract operators
    {

        if(negation)
        {
            numbers.push_back("-");
        }
        else
        {
            if(i==0)
            {
                if(input.at(0)=='-')
                {
                    numbers.push_back("-");
                    i++;
                }
                else
                {
                    numbers.push_back("");
                }
            }
            else
            {
                numbers.push_back("");
            }

        }

        while(input.at(i)>='0'&&input.at(i)<='9'||input.at(i)=='.')
        {
            numbers.back()+=input.at(i);
            if(i<input.size()-1)
            {
                i++;
            }
            else
            {
                break;
            }

        }

        if(input.at(i)=='^'||input.at(i)=='/'||input.at(i)=='*'||input.at(i)=='+'||input.at(i)=='-')
        {
            //tmp = "";
            //tmp += input.at(i);
            operators.push_back(input.at(i));
            if(input.at(i+1)=='-')//testing if there is negative number
            {
                negation = 1;
                i++;
            }
            else
            {
                negation = 0;
            }
        }
    }

    //DEBUG
    //printf("OPS:");
    //printstrvec(operators);
    //printf("NUM:");
    //printstrvec(numbers);


    if(numbers.size()==operators.size()+1)
    {
        long oi = 0;
        bool breaker = 0;

        while(numbers.size()>1)
        {
            oi = 0;
            breaker = 0;
            for(oi=0; oi<operators.size()||breaker; oi++)
            {
                if(operators.at(oi)=='^')
                {
                    str_pow(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 1;
                    break;
                }
            }
            for(oi=0; oi<operators.size()||breaker; oi++)
            {
                if(operators.at(oi)=='*')
                {
                    str_mul(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 1;
                    break;
                }
                if(operators.at(oi)=='/')
                {
                    str_div(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 1;
                    break;
                }
            }
            for(oi=0; oi<operators.size()||breaker; oi++)
            {
                if(operators.at(oi)=='+')
                {
                    str_add(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 1;
                    break;
                }
                if(operators.at(oi)=='-')
                {
                    str_sub(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 1;
                    break;
                }
            }
            //DEBUG
            //printf("END(%d==1)?\n",numbers.size());
            //printf("tpsres:'%s'\n",numbers.at(0).c_str());
        }
    }
    else
    {
        printf("Error with amount of operators related to numbers!\n");
    }
    output=numbers.at(0);
    printf("rettermcalc:'%s'\n",output.c_str());
}

class calc_contain
{

void clean(std::string& Astr)
{
    long i;
    for(i=1; i < Astr.size(); i++)
    {
        if(Astr.at(i)=='-'&&Astr.at(i-1)=='-')
        {
            Astr.erase(Astr.begin()+i);
        }
        if(Astr.at(i)=='-'&&Astr.at(i-1)=='+')
        {
            Astr.erase(Astr.begin()+i-1);
        }
        if(Astr.at(i)=='+'&&Astr.at(i-1)=='-')
        {
            Astr.erase(Astr.begin()+i);
        }
        if(Astr.at(i)=='+'&&Astr.at(i-1)=='+')
        {
            Astr.erase(Astr.begin()+i);
        }
    }
}
void clean(calc_contain* obj)
{
    long i;
    for(i=1; i < obj->calc_str_A.size(); i++)
    {
        if(obj->calc_str_A.at(i)=='-'&&obj->calc_str_A.at(i-1)=='-')
        {
            obj->calc_str_A.erase(obj->calc_str_A.begin()+i);
        }
        if(obj->calc_str_A.at(i)=='-'&&obj->calc_str_A.at(i-1)=='+')
        {
            obj->calc_str_A.erase(obj->calc_str_A.begin()+i-1);
        }
        if(obj->calc_str_A.at(i)=='+'&&obj->calc_str_A.at(i-1)=='-')
        {
            obj->calc_str_A.erase(obj->calc_str_A.begin()+i);
        }
        if(obj->calc_str_A.at(i)=='+'&&obj->calc_str_A.at(i-1)=='+')
        {
            obj->calc_str_A.erase(obj->calc_str_A.begin()+i);
        }
    }
    //DEBUG
    //printf("B[%d]:%s\n",obj->calc_str_B.size(),obj->calc_str_B.c_str());
    for(i=1; i < obj->calc_str_B.size(); i++)
    {
        if(obj->calc_str_B.at(i)=='-'&&obj->calc_str_B.at(i-1)=='-')
        {
            obj->calc_str_B.erase(obj->calc_str_B.begin()+i);
        }
        if(obj->calc_str_B.at(i)=='-'&&obj->calc_str_B.at(i-1)=='+')
        {
            obj->calc_str_B.erase(obj->calc_str_B.begin()+i-1);
        }
        if(obj->calc_str_B.at(i)=='+'&&obj->calc_str_B.at(i-1)=='-')
        {
            obj->calc_str_B.erase(obj->calc_str_B.begin()+i);
        }
        if(obj->calc_str_B.at(i)=='+'&&obj->calc_str_B.at(i-1)=='+')
        {
            obj->calc_str_B.erase(obj->calc_str_B.begin()+i);
        }
    }
}

void inner_calc(std::string& ret_calc_and_before,calc_contain* layer)
{
    //DEBUG
    //printf("innercalcinp:'%s'\n",ret_calc_and_before.c_str());
    std::string str_next = ret_calc_and_before;
    if(layer->next==0)
    {
        std::string tmp = layer->calc_str_A;
        ret_calc_and_before = "";
        str_term_calc(tmp,str_next);
        ret_calc_and_before = str_next;
        printf("retinnercalcA:'%s'\n",ret_calc_and_before.c_str());
    }
    else
    {
        //DEBUG
        //printf("notdeepest!\n");
        std::string tmp = layer->calc_str_A;
        tmp += ret_calc_and_before;
        tmp += layer->calc_str_B;
        ret_calc_and_before = "";
        str_term_calc(tmp,str_next);
        ret_calc_and_before = str_next;
        printf("retinnercalcB:'%s'\n",ret_calc_and_before.c_str());
    }

}

public:
std::string calc_str_A;
calc_contain* next;
std::string calc_str_B;

calc_contain()
{
    next = 0;
    calc_str_A = "";
    calc_str_B = "";
}

~calc_contain()
{
    if(next!=0)
    {
        next->~calc_contain();
    }
    next = 0;
}

void load(std::string& term)
{
    long a = 0;
    long b = term.size()-1;

    while(term.at(a)!='('&&a<term.size()-1)
    {
        a++;
    }
    while(term.at(b)!=')'&&b>0)
    {
        b--;
    }
    if(a<term.size()-1)
    {
        intervalstrcopy(term,calc_str_A,0,a-1);
    }
    if(b>0)
    {
        intervalstrcopy(term,calc_str_B,b+1,term.size()-1);
    }
    if(a==term.size()-1&&b==0)
    {
        //DEBUG
        //printf("NO Bracket!\n");

        intervalstrcopy(term,calc_str_A,0,a);
    }

    this->clean(this);
    //DEBUG
    //printf("a=%d:%s\n",a,calc_str_A.c_str());
    //printf("b=%d:%s\n",b,calc_str_B.c_str());

    if(a<=b&&a<term.size()-1&&b>=0)
    {
        std::string inner = "";
        intervalstrcopy(term,inner,a+1,b-1);
        //DEBUG
        printf("inbracket:'%s'\n",inner.c_str());

        next = new calc_contain();
        next->load(inner);
    }

}



double calculate()
{
    calc_contain* deepest = this;
    std::vector<calc_contain*> layer;
    layer.push_back(deepest);
    while(deepest->next!=0)
    {
        deepest=deepest->next;
        layer.push_back(deepest);
    }

    double result = 0;
    long i = layer.size()-1;
    std::string str_res = "";

    //DEBUG
    printf("layers:%d\n",i);

    while(i>=0)
    {
        inner_calc(str_res,layer.at(i));
        //printf("tmpc:%s\n",str_res.c_str());
        clean(str_res);
        //DEBUG
        //printf("tmpc:%s\n",str_res.c_str());
        i--;
    }

    sscanf(str_res.c_str(),"%lf",&result);


    return result;
}





};


}


