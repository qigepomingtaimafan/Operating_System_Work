#include "process.h"
#include "resource.h"
#include <list>
#include <queue>
#include <vector>
#include <iostream>
//------------------------------
using std::string;
using std::vector;
using std::list;
//------------------------------
class Manager
{
    public:
        list<PCB*> systemList;
        list<PCB*> userList;
        list<PCB*> initList;
        PCB* runningProcess;
        string releaseName;
    private:
        list<RCB*> resources;
        list<PCB*> processes;
        Manager();
        static Manager* manager;
        istream *in;
        ostream *out;
        unsigned int line;
    public:
        PCB* CreateProcess(int PID,Priority priority);
        void DestroyProcess(int PID);
        void RemoveProcess(Priority priority,PCB* pcb);
        void InsertProcess(Priority priority,PCB* pcb);
        static Manager* getInstance();
        RCB* Get_RCB(int rid);
        PCB* FetchPCB(int pid);
        RCB* FetchRCB(int rid);
        RCB* FetchRCB(sting name);
        void Init();
        void Cr(string x,Priority priority);
        void List(string option);
        void To();
        void Req(string name,int n);
        void De(string name);
        void SwitchInOut(string option);
        void PrintLineNum();
        void Time_out();
        void Preempt();
        void Scheduler();
}
