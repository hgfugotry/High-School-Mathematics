#include"./arithmeticOfStdString.h"
#include<iostream>
#include<vector>
int main(int argc,char* argv[])
{
    std::vector<std::string> strvec;
    for(int i=1;i<argc;i++)
        strvec.push_back(calculateStdStringExpression(argv[i]));
    for(std::string str:strvec)
        std::cout<<str<<std::endl;
}