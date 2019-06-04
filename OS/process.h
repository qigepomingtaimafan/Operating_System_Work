#include "resource.h"i
#include "manager.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <pair>
//------------------------------------------
using std::string;
using std::vector;
using std::list;
using std::pair;
using std::map;
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
        map<RCB*,int> resources;
        PS type;
        RCB* blockList;
        PCB* parent;
        list<PCB* > children;
        Priority priority;
        Manager* manager;
    public:
        ProcessingControlBlock(int PID,Priority priority);
        void Link(PCB* parent);
        void KillTree();
        void Request(int rid);
        void Request(int rid,int n);
        void setManager(Manager* manager){this->manager = manager;}
        Manager* getManager(){return manager;}
        PCB* getParent(){return parent;}
        void setParent(PCB* parent){this->parent = parent;}
        void setChildren(PCB* children){this->children.push_back(children);}
}
