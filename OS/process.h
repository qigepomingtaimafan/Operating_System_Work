#ifndef HEADER_PROCESS
#define HEADER_PROCESS

#include "priority.h"
#include "resource.h"
#include "manager.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <utility>
//------------------------------------------
using std::string;
using std::vector;
using std::list;
using std::pair;
using std::map;
//------------------------------------------
enum PS
{
    none,
    ready,
    running,
    blocked
};
//------------------------------------------
class RCB;
class Manager;
class PCB
{
    public:
        string name;
        int PID;
        int cpuState;
        int memory;
        int open_Files;
        map<RCB*,int> resources;
        PS type;
        RCB* blockList;
        list<PCB*> * readyList;
        list<PCB*> * RL; 
        PCB* parent;
        list<PCB* > children;
        Priority priority;
        Manager* manager;
    public:
        PCB(int PID,Priority priority);
        void Link(PCB* parent);
        void KillTree();
        void Request(int rid);
        void Request(int rid,int n);
        void setManager(Manager* manager){this->manager = manager;}
        Manager* getManager(){return manager;}
        PCB* getParent(){return parent;}
        void setParent(PCB* parent){this->parent = parent;}
        void setChildren(PCB* children){this->children.push_back(children);}
        void Release(int rid);
        void Release(int rid,int n);
        void Scheduler();
};
//------------------------------------------
#endif
