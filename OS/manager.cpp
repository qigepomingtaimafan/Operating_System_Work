#include "resource.h"
#include "manager.h"
#include "process.h"
#include <vector>
//--------------------------------
using std::vector;
//--------------------------------
static Manager* Manager::getManager()
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
    for (iter = processes;iter != processed.end();iter++)
    {
        if(*iter->getPID() == PID)
        {
            *iter->KillTree();
            delete *iter;
        }
    }
    Scheduler();
}
