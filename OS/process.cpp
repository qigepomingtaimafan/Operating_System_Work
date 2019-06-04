#include "process.h"
#include <string>
#include <list>
#include <map>
//-----------------------------------
using std::string;
using std::list;
using std::map;
//-----------------------------------
Process::Process()
{
    type = none;
}

void Process::Create()
{
    type = ready;
}

void Process::destroy()
{
    type = none;
}

void Process::Request()
{
    type = blocked;
}

void Process::Release()
{
    type = ready;
}

void Process::Time_out()
{
    type = ready;
}
void Process::Dispatch(bool toReady)
{
    if (toReady)
    {
        type = ready;
    }
    else
    {
        type = running;
    }
}

ProcessingControlBlock::ProcessingControlBlock(int PID,Priority priority)
{
    this->PID = PID;
    this->priority = priority;
    this->type = none;
}

void Process::KillTree()
{
    list<PCB*>::iterator iterp;
    for (iterp = children.begin();iterp != children.end();iterp++)
    {
        *iterp->KillTree();
        delete *iterp;
        children.erase(iterp);
    }
    list<RCB*>::iterator iter;
    for (iter = resources.begin();iter != resources.end();iter++)
    {
        (*iter.first)->DeleteProcess(this->PID);
    }
}

void ProcessingControlBlock::Request(int rid)
{
    RCB* r = getManager()->Get_RCB(rid);
    if (r->getStatus() == 1)
    {
        r->setStatus(0);
        resources[r] = 1;
    }
    else
    {
        type = blocked;
        blockList = r;
        getManager()->RemoveProcess(priority,this);
        r->InsertProcess(this);
        Scheduler();
    }

}

void ProcessingControlBlock::Request(int rid,int n)
{
    RCB* r = getManager()->Get_RCB(rid);
    if (r->getStatus() >= n)
    {
        int m = r->getStatus()-n;
        r->setStatus(m);
        resources[r] = n;   
    }
    else
    {
        if (n > r->getRID())
        {
            getManager->Error(1);
            return;
        }
        type = blocked;
        blockList = r;
        getManager()->RemoveProcess(priority,this);
        r->InsertProcess(this);
        Scheduler();
    }
}
