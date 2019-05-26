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
    Words words;
    string temp;
    if(!in.is_open() || !out.is_open())
        printf("The a.pas is not exist or can not open a.dvd\n");
    else
    {
        string temp;
        string s;
        int lineNum = 1;
        while(getline(in,temp))
        {   
            //s += temp;
        //}
        words.SetInput(temp);
        words.SetLineNum(lineNum);
        //words.SetInput(s);
        while (1)
        {
            Word *word = words.LexAnalyze();
            if(word == NULL)
                break;
            else
            {
                if(word->GetVal() == 99 && word->GetNum() ==99)
                    break;
                out<<"("<<word->GetNum()<<",";
                if(word->GetVal() == 0)
                    out<<"-)"<<endl;
                else
                    out<<word->GetVal()<<")"<<endl;
                delete(word);
            }
        }
        lineNum++;
        }
        in.close();
        out.close();
        if(words.IsComplete())
            printf("--------------------------------------\ncomplete\n");
        else
            printf("--------------------------------------\nPlease check the error uppon\n");
    }
    return 0;
}
