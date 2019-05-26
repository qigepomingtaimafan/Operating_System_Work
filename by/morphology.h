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
        int GetNum(){return num;}
        int GetVal(){return val;}
};

class Words
{
    private:
        char character;
        string token;
        int lineNum;
        string::iterator input; 
        map<string,int> reserveMap;
        map<string,int> symbolMap;
        map<string,int> constantMap;
        bool complete;
    public:                
        Words(){InitReserveMap();complete = true;}
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
        void Error(int kind);
        Word* CreateWord(int num,int val);
        void InitReserveMap();
        void SetInput(string &s){input = s.begin();}
        void SetLineNum(int lineNum){this->lineNum = lineNum;}
        bool IsComplete(){return complete;}
};


