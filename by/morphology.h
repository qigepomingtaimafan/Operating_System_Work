#include <iostream>
#include <string>


class Word
{

    private:
        int num;
        int val;

}

class Words
{
    private:
        char character;
        string token;
        char * input; 
    public:                
        Word* LexAnalyze();
        void GetChar();
        void GetNbc();
        void Concat();
        bool Letter();
        bool Digit();
        int Reserve();
        int Constant();
        void Error();
        Word* CreateWord(int num,int val);
}


