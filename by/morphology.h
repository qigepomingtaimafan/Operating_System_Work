#include <iostream>
#include <string>
#include <map>
//-----------------------------------------
using std::string;
using std::map;
//-----------------------------------------
class Word
{
    private:
        int num;
        int val;
    public:
        Word(int num,int val){this->num = num;this->val = val;}
        int getNum(){return num;}
        int getval(){return val;}
};

class Words
{
    private:
        char character;
        string token;
        char * input; 
        map<string,int> reserveMap;
        map<string,int> symbolMap;
        map<string,int> constantMap;
    public:                
        Word* LexAnalyze();
        void GetChar();
        void Getnbc();
        void Concat();
        bool Letter();
        bool Digit();
        void Retract();
        int Symbol();
        int Reserve();
        int Constant();
        void Error();
        Word* CreateWord(int num,int val);
        void InitReserveMap();
        void SetInput(const string s){input = &s[0];}
};


