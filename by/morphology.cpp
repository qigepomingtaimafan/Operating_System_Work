#include "morphology.h"
#include <string>
#include <map>
#include <stdio.h>
//--------------------------------------------
#define BEGIN 1
#define END 2
#define INT 3
#define IF 4
#define THEN 5
#define ELSE 6
#define FUNCTION 7
#define READ 8
#define WRITE 9
#define SYMBOL 10
#define CONSTANT 11
#define E 12
#define NE 13
#define LE 14
#define L 15
#define GE 16
#define G 17
#define SUB 18
#define MUL 19
#define ASSIGN 20
#define LPAR 21
#define RPAR 22
#define SEM 23
//-------------------------------------------
using std::string;
using std::map;
using std::endl;
//-------------------------------------------
Word* Words::LexAnalyze()
{
    token = "";
    GetChar();
    Getnbc();

    switch(character)
    {
        case 'a' :
        case 'b' :
        case 'c' :
        case 'd' :
        case 'e' :
        case 'f' :
        case 'g' :
        case 'h' :
        case 'i' :
        case 'j' :
        case 'k' :
        case 'l' :
        case 'm' :
        case 'n' :
        case 'o' :
        case 'p' :
        case 'q' :
        case 'r' :
        case 's' :
        case 't' :
        case 'u' :
        case 'v' :
        case 'w' :
        case 'x' :
        case 'y' :
        case 'z' :
        case 'A' :
        case 'B' :
        case 'C' :
        case 'D' :
        case 'E' :
        case 'F' :
        case 'G' :
        case 'H' :
        case 'I' :
        case 'J' :
        case 'K' :
        case 'L' :
        case 'M' :
        case 'N' :
        case 'O' :
        case 'P' :
        case 'Q' :
        case 'R' :
        case 'S' :
        case 'T' :
        case 'U' :
        case 'V' :
        case 'W' :
        case 'X' :
        case 'Y' :
        case 'Z' :
        {
            while(Letter() || Digit())
            {
                Concat();
                GetChar();
            }
            Retract();
            int num = Reserve();
            if (num != 0)
            {
                return CreateWord(num,token);
            }
            else
            {
                int val = Symbol();
                return CreateWord(SYMBOL,token);
            }
            break;
        }
        case '0' :
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
        {
            while(Digit())
            {
                Concat();
                GetChar();
            }
            Retract();
            int val = Constant();
            return CreateWord(CONSTANT,token);
            break ;
        }
        case '<' :
        {
            GetChar();
            if(character == '=')
                return CreateWord(LE,"<=");
            else if (character == '>')
                return CreateWord(NE,"<>");
            else 
            {
                Retract();
                return CreateWord(L,"<");
            }
            break;
        }
        case '>' :
        {
            GetChar();
            if(character == '=')
                return CreateWord(GE,">=");
            else
            {
                Retract();
                return CreateWord(G,">");
            }
            break;
        }
        case '=' :
            return CreateWord(E,"=");
            break;
        case '-' :
            return CreateWord(SUB,"-");
            break;
        case '*' :
            return CreateWord(MUL,"*");
            break;
        case '(' :
            return CreateWord(LPAR,"(");
            break;
        case ')' :
            return CreateWord(RPAR,")");
            break;
        case ';' :
            return CreateWord(SEM,";");
            break;
        case ':' :
        {
            GetChar();
            if(character == '=')
                return CreateWord(ASSIGN,":=");
            else
            {
                token += ":";
                token += character;
                Error(2);
                return CreateWord(99,"Error");
            }
            break;
        }
        case '\000':
            return CreateWord(99,"Error");
            break;
        default :
            Error(1);
            CreateWord(99,"Error");
            break;          
    }
    return NULL;
}


Word* Words::CreateWord(int val,string s)
{
    Word * word = new Word(val,s);
    return word;
}

void Words::GetChar()
{
    character = *input;
    input++;
}

void Words::Getnbc()
{
    while (character == ' ')
    {
        GetChar();
    }
}

void Words::Concat()
{
    token += character;
}

bool Words::Letter()
{
    if ((character>=97 && character <=122)||(character>=65 && character<=90))
        return true;
    else
        return false;
}

bool Words::Digit()
{
    if (character>=48 && character<=57)
        return true;
    else
        return false;
}

void Words::Retract()
{
    character = ' ';
    input --;
}

int Words::Reserve()
{
    map<string,int>::iterator iter;
    iter = reserveMap.find(token);
    if(iter == reserveMap.end())
        return 0;
    else
        return iter->second;
}

void Words::InitReserveMap()
{
    reserveMap["begin"] = 1;
    reserveMap["end"] = 2;
    reserveMap["integer"] = 3;
    reserveMap["if"] = 4;
    reserveMap["then"] = 5;
    reserveMap["else"] = 6;
    reserveMap["function"] = 7;
    reserveMap["read"] = 8;
    reserveMap["write"] = 9;
}

int Words::Symbol()
{
    map<string,int>::iterator iter;
    iter = symbolMap.find(token);
    if(iter == symbolMap.end())
    { 
        symbolMap[token] = symbolMap.size()+1;
        return symbolMap.size();
    }
    else
        return iter->second;
}

int Words::Constant()
{
        
    map<string,int>::iterator iter;
    iter = constantMap.find(token);
    if(iter == constantMap.end())
    { 
        constantMap[token] = constantMap.size()+1;
        return constantMap.size();
    }
    else
        return iter->second;
}

void Words::Error(int kind)
{
    complete = false;
    printf("--------------------------------------\n");
    printf("Error happened in line %d\n",lineNum);   
    switch(kind)
    {
       case 1:
             {
                printf("There is illegal character : \"%c\"\n",character); 
                err<<"*** LINE:"<<lineNum<<" There is illegal character : "<<"\""<<character<<"\""<<endl;
                break;
             }
       case 2:
             {
                printf("Illegal symbol \"%s\"\n",token.c_str());
                err<<"*** LINE:"<<lineNum<<" Illegal symbol : "<<"\""<<token<<"\""<<endl;
                break;
             }
    }
}

bool Words::SetErr(string errS)
{
    err.open(errS,std::ios::out);
    return err.is_open();
}
