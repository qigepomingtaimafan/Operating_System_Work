#include <iostream>
#include <fstream>
#include <string>
#include <map>
//-----------------------------------------
using std::string;
using std::map;
using std::ofstream;
//-----------------------------------------
class Word
{
    private:
        string  s;
        int val;
    public:
        Word(int val,string s){this->s = s;this->val = val;}
        string GetS(){return s;}
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
        ofstream err;
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
        Word* CreateWord(int val,string s);
        void InitReserveMap();
        void SetInput(string &s){input = s.begin();}
        void SetLineNum(int lineNum){this->lineNum = lineNum;}
        bool IsComplete(){return complete;}
        bool SetErr(string errS);
};


