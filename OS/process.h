#include "resource.h"
#include <string>
#include <vector>
#include <list>
//------------------------------------------
using std::string;
using std::vector;
using std::list;
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
        void Dispatch(bool toReady);
}

class ProcessingControlBlock:public Process
{
    private:
        int PID;
        int cpuState;
        int memory;
        int open_Files;
        list<RCB*> resources;
        PS type;
        PCB* list;
        PCB* parent;
        list<PCB* > children;
        Priority priority;
    public:
        ProcessingControlBlock(int PID,Priority priority);
        void Link(PCB* parent);
        void KillTree();
}
