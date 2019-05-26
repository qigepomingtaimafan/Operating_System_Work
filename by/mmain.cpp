#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "morphology.h" 
#define LINE 1024
//--------------------------------------
using std::string;
using std::map;
using std::ifstream;
using std::ofstream;
//--------------------------------------
int main()
{
    ifstream in("a,pas",std::ios::in);
    ofstream out("a.dvd",std::ios::app);
    Words words;
    string temp;
    if(in == NULL || out == NULL)
        printf("The a.pas is not exist or can not open a.dvd");
    else
    {
        string temp;
        while(getline(in,temp))
        {
            words.SetInput(temp);
            Word *word = words.LexAnalyze();
            if(!word)
            {
                printf("There is error");
            }
            out<<"("<<word.GetNum()<<",";
            if(word.GetVal()==0)
                out<<"-)"<<endl;
            else
                out<<word.GetVal()<<")"<<endl;
            delete(word);
        }
        in.close();
        out.close();
        printf("complete");
    }
    return 0;
}
