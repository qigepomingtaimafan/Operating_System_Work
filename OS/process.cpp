#include<process.h>
#include<string>
//-----------------------------------
using std::string;
//-----------------------------------
Process::Process()
{
    ps = none;
}

void Process::Create()
{
    ps = ready;
}

void Process::destroy()
{
    ps = none;
}

void Process::Request()
{
    ps = blocked;
}

void Process::Release()
{
    ps = ready;
}

void Process::Time_out()
{
    ps = ready;
}
void Process::Dispatch(bool toReady)
{
    if (toReady)
    {
        ps = ready;
    }
    else
    {
        ps = running;
    }
}

ProcessingControlBlock::ProcessingControlBlock(int PID,Priority priority)
{
    this->PID = PID;
    this->priority = priority;
    this->ps = none;
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
