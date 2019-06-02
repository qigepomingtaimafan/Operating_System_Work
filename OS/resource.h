#include<iostream>
#include<process.h>
#include<string>
//------------------------------
using std::string;
//------------------------------
typedef ResourceControlBlock RCB;
//------------------------------
class ResourceControlBlock
{
    private:
        int RID;
        int status;
        PCB* waitingList;
}
