#include "morphology.h"
#include "string"
--------------------------------------------
#define SYMBOL 1
#define CONSTANT 2
#define INT 3
#define IF 4
#define ELSE 5
#define WHILE 6
#define FOR 7
#define READ 8
#define WRITE 9
#define ADD 10
#define SUB 11
#define MUL 12
#define DIV 13
#define L 14
#define LE 15
#define G 16
#define GE 17
#define NE 18
#define E 19
#define ASSIGN 20
#define LPAR 21
#define RPAR 22
#define COM 23
#define SEM 24
-------------------------------------------
Word* Words::LexAnalyze()
{
    token = "";
    GetChar();
    GetNbc();

    switch(character)
    {
        case'a':
        case'b':
        case'c':
        case'd':
        case'e':
        case'f':
        case'g':
        case'h':
        case'i':
        case'j':
        case'k':
        case'l':
        case'm':
        case'n':
        case'o':
        case'p':
        case'q':
        case'r':
        case's':
        case't':
        case'u':
        case'v':
        case'w':
        case'x':
        case'y':
        case'z':
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
        case'0':
        case'1':
        case'2':
        case'3':
        case'4':
        case'5':
        case'6':
        case'7':
        case'8':
        case'9':
            while(Digit())
            {
                Concat();
                GetChar();
            }
            restract();
            int val = Constant();
            return CreateWord(CONSTANT,val);
            break ;
        case'<':
            GetChar();
            if(character = '=')
                return CreateWord(LE,0);
            else
            {
                Retract();
                return CreateWord(L,0);
            }
            break;
        case'>':
            GetChar();
            if(character == '=')
                return CreateWord(GE,0);
            else
            {
                Retract();
                return CreateWord(G,0);
            }
            break;
        case'=':
            GetChar();
            if(character == '=')
                return CreateWord(E,0);
            else
            {
                Retract();
                return CreateWord(ASSIGN,0);
            }
            break;
        case'!':
            GetChar();
            if(character == '=')
                return CreateWord(NE,0);
            else
                Error();
            break;
        case'+':
            return CreateWord(ADD,0);
            break;
        case'-':
            return CreateWord(SUB,0);
            break;
        case'*':
            return CreateWord(MUL,0);
            break;
        case'/':
            return CreateWord(DIV,0);
            break;
        case'(':
            return CreateWord(LPAR,0);
            break;
        case')':
            return CreateWord(RPAR,0);
            break;
        case',':
            return CreateWord(COM,0);
            break;
        case';':
            return CreateWord(SEM,0);
            break;
        default:
            Error();
            break;          
    }
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
}


