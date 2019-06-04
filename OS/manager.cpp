#include "resource.h"
#include "manager.h"
#include "process.h"
#include <vector>
//--------------------------------
using std::vector;
//--------------------------------
Manager* Manager::getManager()
{
    if(manager == NULL)
    {
        manager = new Manager();
    }
    return manager;
}

Manager::Manager()
{
    for(int i =0;i<4;i++)
    {
        RCB* rcb = new RCB(i+1,i+1);
        resources.push_back(rcb);
    }
}

void Manager::DestroyProcess(int PID)
{
    vector<PCB*>::iterator iter;
    for (iter = processes.begin();iter != processes.end();iter++)
    {
        if(*iter == NULL)
            continue;
        if(*iter->getPID() == PID)
        {
            *iter->KillTree();
            delete *iter;
        }
    }
    Scheduler();
}

RCB* Manager::Get_RCB(int rid)
{
    vector<RCB*>::iterator iter;
    for (iter = resources.begin();iter != resources.end();iter++)
    {
        if(*iter == NULL)
            continue;
        if(*iter->getRID() == rid)
        {
            return *iter;
        }
    }
}

void Manager::CreateProcess(int PID,Priority priority)
{
    PCB* pcb = new PCB(PID,priority);
    pcb->setParent(runningProcess);  
    runningProcess->setChildren(pcb);
    switch(priority)
    {
        case init:
        {
            initList.push_back(pcb);
            break;
        }
        case system:
        {
            systemList.push_back(pcb);
            break;
        }
        case user:
        {
            userList.push_back(pcb);
            break;
        }
    }
    Scheduler();
}

void Manager::RemoveProcess(Priority priority,PCB* pcb)
{
    list<PCB*> & l;
    switch(priority)
    {
        case init:
        {
            l = initList;
            break;
        }
        case system:
        {
            l = systemList;
            break;
        }
        case user:
        {
            l = userList;
            break;
        }
    }
    list<PCB*>::iterator iter;
    for (iter = l.begin();iter != l.end();iter++)
    {
        if (*iter == pcb)
        {
            l.erase(iter);
            return ;
        }
    }
    
    
}
