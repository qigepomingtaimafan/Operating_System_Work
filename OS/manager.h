#ifndef HEADER_MANAGER
#define HEADER_MANAGER

#include "priority.h"
#include "process.h"
#include "resource.h"
#include <list>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
//------------------------------
using std::string;
using std::vector;
using std::list;
using std::ifstream;
using std::ofstream;
//------------------------------
class RCB;
class PCB;
class Manager
{
    public:
        list<PCB*> systemList;
        list<PCB*> userList;
        list<PCB*> initList;
        PCB* runningProcess;
        string releaseName;
        list<RCB*> resources;
        list<PCB*> processes;
    private:
        ifstream in;
        ofstream out;
        int line;
        bool terminal;
    public:
        PCB* CreateProcess(int PID,Priority priority);
        void DestroyProcess(int PID);
        void RemoveProcess(Priority priority,PCB* pcb);
        void InsertProcess(Priority priority,PCB* pcb);
        PCB* FetchPCB(int pid);
        RCB* FetchRCB(int rid);
        RCB* FetchRCB(string name);
        void Init();
        void Cr(string x,Priority priority);
        void List(string option);
        void To();
        void Req(string name,int n);
        void De(string name);
        void SwitchInOut(string option);
        void PrintLineNum();
        void Time_out();
        void Preempt(PCB* p);
        void Scheduler();
        void PrintString(string s);
        void Error(int n);
};

#endif
