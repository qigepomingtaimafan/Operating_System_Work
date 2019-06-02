#include <iostream>
#include <resource.h>
#include<string>
//------------------------------------------
using std::string;
//------------------------------------------
enum ProcessState
{
    none,
    ready,
    running,
    blocked
};
enum Priority
{
    init,
    user,
    system
};
//------------------------------------------
typedef ProcessState PS;
typedef ProcessingControlBlock PCB;
//------------------------------------------
class Process
{
    private:
        PS ps;
    public:
        Process();
        void Create();
        void destroy();
        void Request();
        void Release();
        void Time_out();
        void Dispatch();
}
class ProcessingControlBlock:public Process
{
    private:
        string PID;
        int cpuState;
        int memory;
        int open_Files;
        RCB* resources;
        PS type;
        PCB* list;
        PCB* parent;
        PCB* children;
        Priority priority;
}
