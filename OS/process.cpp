#include "process.h"
#include <string>
#include <list>
#include <map>
//-----------------------------------
using std::string;
using std::list;
using std::map;
//-----------------------------------
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
    }
    map<RCB*,int>::iterator iter;
    for(iter = resources.begin(); iter != resources.end();iter++)
    {
        if(iter->first = getManager()->*(resources.first()))
        {
            Release(iter->first->RID);
            getManager()->releaseName += ",";
            getManager()->releaseName += (iter->first->name);
        }
        else
        {
            Release(iter->first->RID,iter->second);
            getManager()->releaseName += ",";
            getManager()->releaseName += (iter->first->name);

        }
    }
    delete this;
}

void ProcessingControlBlock::Request(int rid)
{
    RCB* r = getManager()->FetchRCB(rid);
    if (r->status == 1)
    {
        r->status = 0
        resources[r] = 1;
    }
    else
    {
        type = blocked;
        blockList = r;
        readyList = NULL;
        getManager()->RemoveProcess(priority,this);
        r->waitingList.push_back(pair(this,1));
        getManager()->Scheduler();
    }

}

void ProcessingControlBlock::Request(int rid,int n)
{
    RCB* r = getManager()->Fetch(rid);
    if (r->status >= n)
    {
        int m = r->status-n;
        r->status = m;
        if(resources.count(r) == 0)
        {
            resources[r] = n; 
        }
        else
        {
            int j = resources[r];
            j += n;
            resources[r] = j;
        }
    }
    else
    {
        if (n > r->k)
        {
            Manager::Error(2);
            return;
        }
        type = blocked;
        blockList = r;
        readyList = NULL;
        getManager()->RemoveProcess(priority,this);
        r->waitingList.push_back(this,n);
        getManager()->Scheduler();
    }
}

void ProcessingControlBlock::Release(int rid)
{
    RCB* r = getManager()->FetchRCB(rid);
    map<RCB*,int>::iterator iter = resources.find(r);
    if(iter != resources.end())
    {
        resources.erase(iter);
    }
    if(r->waitingList.size() == 0)
    {
        r->status = 0;
    }
    else
    {
        list<pair<PCB*> >::iterator iterl = waitingList.begin();
        PCB* q = *iterl;
        r->waitingList.erase(iterl);
        q->status = ready;
        q->readyList = RL;
        q->blockList = NULL;
        q->resource.push_back(r);
        q->readyList.push_back(q);
        getManager()->Scheduler();
    }
}

void ProcessingControlBlock::Release(int rid,int n)
{
    RCB* r = getManager()->FetchRCB(rid);
    r->status = r->status+n;
    resource.erase(resource.find(r));
    list<pair<PCB*,int> >::iterator iter = waitingList.begin();
    while(r->waitingList.size() !=0 && r->status >= *iter.second)
    {
        r->status = r->status - *iter.second;
        PCB* q = *iter;
        r->waitingList.erase(iter);
        q->status = ready;
        q->readyList = RL;
        q->blockList = NULL;
        if(q->resource.find(r))
        {
            int j = resource[r];
            resource[r] = j+n;
        }
        else
        {
            resource[r] = n;
        }
        q->readyList.push_back(q);
    }
    getManager()->Scheduler();
}

