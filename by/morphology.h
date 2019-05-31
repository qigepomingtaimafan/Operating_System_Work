#include <iostream>
#include <fstream>
#include <string>
#include <map>
//-----------------------------------------
using std::string;
using std::map;
using std::ofstream;
//-----------------------------------------
class Word //Single word class
{
    private:
        string  s; //the symbol of word
        int val; //the kind of word(number)
    public:
        Word(int val,string s){this->s = s;this->val = val;}
        string GetS(){return s;}
        int GetVal(){return val;}
};

class Words //The set of lots of word
{
    private:
        char character; //Newest word has been read in 
        string token; //String has been read
        int lineNum; //Number of line now
        string::iterator input; //Iterator of string from getline()
        map<string,int> reserveMap; //map of Resetve word
        map<string,int> symbolMap; //deleted
        map<string,int> constantMap; //deleted
        bool complete; //If there is some error in morphology complete will be false
        ofstream err; //The err file 
    public:                
        Words(){InitReserveMap();complete = true;}
        Word* LexAnalyze(); //The mainly funcion,judge if word is right according symbol table 
        void GetChar(); //read a letter into character
        void Getnbc(); //read not blank word
        void Concat(); //contact the character and token
        bool Letter(); //judge character is a letter 
        bool Digit(); // judge character is a digit
        void Retract(); //set back the character to string 
        int Symbol(); //deleted
        int Reserve(); //get the reserve number of token
        int Constant(); //deleted
        void Error(int kind); //deal error 
        Word* CreateWord(int val,string s); //make two return value to a word class
        void InitReserveMap(); //setup reserve map
        void SetInput(string &s){input = s.begin();} //set the itertor to the begin of input string 
        void SetLineNum(int lineNum){this->lineNum = lineNum;}
        bool IsComplete(){return complete;}
        bool SetErr(string errS);
};


