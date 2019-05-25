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
Words::Word* LexAnalyze()
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
            while(letter() || digit())
            {
                concat();
                getchar();
            }
            retract();
            int num = reserve();
            if (num != 0)
            {
                return CreateWord(num,0);
            }
            else
            {
                int val = symbol();
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
            while(digit())
            {
                concat();
                GetChar();
            }
            restract();
            int val = constant();
            return CreateWord(CONSTANT,val);
            break ;
        case'<':
            getchar();
            if(character = '=')
                return CreateWord(LE,0);

    }

}


Word* CreateWord(int num,int val)
{
    Word * word = new Word(num,val);
    return word;
}
