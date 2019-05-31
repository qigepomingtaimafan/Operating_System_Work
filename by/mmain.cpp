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
using std::endl;
using std::ofstream;
//--------------------------------------
int main()
{
    ifstream in("a.pas",std::ios::in);
    ofstream out("a.dvd",std::ios::out);
    Words *words= new Words();
    string temp;
    if(!in.is_open() || !out.is_open() || !words->SetErr("a.err"))
        printf("The a.pas is not exist or can not write a.dvd or can not write a.err\n");
    else
    {
        string temp;
        string s;
        int lineNum = 1;
        while(getline(in,temp))
        {   
            words->SetInput(temp);
            words->SetLineNum(lineNum);
            while (1)
            {
                Word *word = words->LexAnalyze();
                if(word == NULL)
                    break;
                else
                {
                    if(word->GetVal() == 99 && word->GetS() =="Error")
                        break;
                    out.setf(std::ios::right);
                    out.width(16);
                    out<<word->GetS()<<" "<<word->GetVal()<<endl;
                    delete(word);
                }
            }
            out.setf(std::ios::right);
            out.width(16);
            out<<"EOLN"<<" "<<"24"<<endl;
            lineNum++;
        }
        out.setf(std::ios::right);
        out.width(16);
        out<<"EOF"<<" "<<"25"<<endl;
        in.close();
        out.close();
        if(words->IsComplete())
            printf("--------------------------------------\ncomplete\n");
        else
            printf("--------------------------------------\nPlease check the error uppon\n");
    }
    delete (words);
    return 0;
}
