#include<iostream>
#include<process.h>
//------------------------------
using std:string;
//------------------------------
class Manager
{
    public:
        void CreateProcess(int PID,Priority priority);
        void DestroyProcess(int PID);
}
