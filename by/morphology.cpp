#include "morphology.h"
#include <string>
#include <map>
#include <stdio.h>
//--------------------------------------------
#define BEGIN 1
#define END 2
#define INT 3
#define IF 4
#define ELSE 5
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
//-------------------------------------------
Word* Words::LexAnalyze()
{
    token = "";
    GetChar();
    GetNbc();

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
            while(Letter() || Digit())
            {
                Concat();
                GetChar();
            }
            Retract();
            int num = Reserve();
            if (num != 0)
            {
                return CreateWord(num,0);
            }
            else
            {
                int val = Symbol();
                return CreateWord(SYMBOL,val);
            }
            break;
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
            while(Digit())
            {
                Concat();
                GetChar();
            }
            restract();
            int val = Constant();
            return CreateWord(CONSTANT,val);
            break ;
        case '<' :
            GetChar();
            if(character = '=')
                return CreateWord(LE,0);
            else if (character = '>')
                return CreateWord(NE,0);
            else 
            {
                Retract();
                return CreateWord(L,0);
            }
            break;
        case '>' :
            GetChar();
            if(character == '=')
                return CreateWord(GE,0);
            else
            {
                Retract();
                return CreateWord(G,0);
            }
            break;
        case '=' :
            return CreateWord(E,0);
            break;
        case '-' :
            return CreateWord(SUB,0);
            break;
        case '*' :
            return CreateWord(MUL,0);
            break;
        case '(' :
            return CreateWord(LPAR,0);
            break;
        case ')' :
            return CreateWord(RPAR,0);
            break;
        case ';' :
            return CreateWord(SEM,0);
            break;
        case ':' :
            GetChar();
            if(character == '=')
                return CreateWord(ASSIGN,0);
            else
            Error();
            break;
        default :
            Error();
            break;          
    }
    return NULL;
}


Word* Words::CreateWord(int num,int val)
{
    Word * word = new Word(num,val);
    return word;
}

void Words::GetChar()
{
    input ++;
    character = *input;
}

void Words::Getnbc()
{
    while (character != ' ')
    {
        getchar();
    }
}

void Words::Concat()
{
    token += character;
}

bool Words::Letter()
{
    if (character>=97 && character <=122)
        return true;
    else
        return false;
}

bool Words::Digit()
{
    if (character>=30 && character<=39)
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

void Words::Error()
{
    printf("Error happened with token %s",token);    
}
