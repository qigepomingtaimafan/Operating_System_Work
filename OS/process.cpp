#include "process.h"
#include <string>
#include <list>
//-----------------------------------
using std::string;
using std::list;
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
        *iter->DeleteProcess(this->PID);
    }
}

void ProcessingControlBlock::Request(int rid)
{
    RCB* r = getManager()->Get_RCB(rid);
    if (r->Status == 1)
    {
        r->Status = 0;
        resources.push_back(this);
    }
    else
    {
        type = blocked;
        list.push_back(r);
        getManager()->RemoveProcess(priority,this);                
    }

}
