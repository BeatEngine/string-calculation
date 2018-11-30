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
    printf("str-copy interval error[%d|%d]!\n",a,b);
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
    printf("str_term_calc_inp:%s\n",input.c_str());
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
        bool breaker = 1;

        while(numbers.size()>1)
        {
            oi = 0;
            breaker = 1;
            for(oi=0; oi<operators.size()&&breaker; oi++)
            {
                //printf("a\n");
                if(operators.at(oi)=='^')
                {
                    str_pow(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 0;
                    break;
                }
            }
            for(oi=0; oi<operators.size()&&breaker; oi++)
            {
                //printf("b\n");
                if(operators.at(oi)=='*')
                {
                    //printf("mul\n");
                    str_mul(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 0;
                    break;
                }
                if(operators.at(oi)=='/')
                {
                    //printf("div\n");
                    str_div(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 0;
                    break;
                }
            }
            //printf("after b\n");
            for(oi=0; oi<operators.size()&&breaker; oi++)
            {
                //printf("c\n");
                if(operators.at(oi)=='+')
                {
                    str_add(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 0;
                    break;
                }
                if(operators.at(oi)=='-')
                {
                    str_sub(numbers.at(oi),numbers.at(oi+1));
                    operators.erase(operators.begin()+oi);
                    numbers.erase(numbers.begin()+oi+1);
                    breaker = 0;
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
    printf("termcalcresult:'%s'\n",output.c_str());
}

class calc_contain
{

void clean(std::string& Astr)
{
    //DEBUG
    //printf("Before:'%s'\n",Astr.c_str());
    long i;
    for(i=1; i < Astr.size(); i++)
    {
        if(Astr.at(i)=='-'&&Astr.at(i-1)=='-')
        {
            Astr.at(i-1) = '+';
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
    //DEBUG
    //printf("After:'%s'\n",Astr.c_str());
}


void inner_calc(std::string& ret_calc_term,calc_contain* layer)
{
    //DEBUG
    //printf("lyrsbrkts%d castr:%d\n",layer->nexts.size(),this->calc_strs.size());
    long i;
    if(layer->nexts.size()==0)
    {
        //DEBUG
        printf("end_str_term_calc:'%s'\n",layer->calc_strs.at(0).c_str());
        std::string tmp_term = "";
        tmp_term = layer->calc_strs.at(0).c_str();
        clean(tmp_term);
        str_term_calc(tmp_term,ret_calc_term);
    }
    else
    {
        std::string tmp_term = "";
        std::string tmp_part;
        for(i=0; i<layer->nexts.size(); i++)
        {

            tmp_part = "";
            inner_calc(tmp_part,layer->nexts.at(i));
            tmp_term+=layer->calc_strs.at(i);
            tmp_term+=tmp_part;
            //printf("%d\n",i);
        }
        //printf("str_term_calc:'%s'\n",tmp_term.c_str());
        clean(tmp_term);
        str_term_calc(tmp_term,ret_calc_term);
    }
    printf("inner_calc_ret:'%s'\n",ret_calc_term.c_str());

}

public:
std::vector<std::string> calc_strs;
std::vector<calc_contain*> nexts;

calc_contain()
{

}

~calc_contain()
{
    for(long i = 0; i < nexts.size(); i++)
    {
        nexts.at(i)->~calc_contain();
    }
}

void load(std::string& term)
{
    long tsz = 0;
    long lbrbcnt = 0;
    calc_strs.push_back("");
    std::vector<std::string> tmp_brackets;
    while(tsz<term.size())
    {

        /*bracketindexloop*/
        if(term.at(tsz)=='(')
        {
            nexts.push_back(new calc_contain());
            calc_strs.push_back("");
            tmp_brackets.push_back("");
            lbrbcnt++;
            tsz++;
            while(lbrbcnt!=0&&tsz<term.size())
            {
                if(term.at(tsz)=='(')
                {
                    lbrbcnt++;
                }
                if(term.at(tsz)==')')
                {
                    lbrbcnt--;
                }
                if(lbrbcnt!=0)
                {
                    tmp_brackets.back()+=term.at(tsz);
                    tsz++;
                }



            }

        }
        else
        {
            calc_strs.back()+=term.at(tsz);
        }



        tsz++;
    }
    long i;
    //DEBUG
    printf("tmpbrackets:\n");
    printstrvec(tmp_brackets);
    printf("thislayer:\n");
    printstrvec(calc_strs);

    for(i = 0; i < nexts.size(); i++)
    {
        nexts.at(i)->load(tmp_brackets.at(i));
    }

}


double calculate()
{
    double result = 0;
    std::string str_result = "";
    this->inner_calc(str_result,this);

    sscanf(str_result.c_str(),"%lf",&result);

    return result;

}



};


}


