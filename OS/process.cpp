#include "process.h"
#include "priority.h"
#include <string>
#include <list>
#include <map>
#include <utility>
//-----------------------------------
using std::string;
using std::list;
using std::map;
using std::pair;
//-----------------------------------
PCB::PCB(int PID,Priority priority)
{
    this->PID = PID;
    this->priority = priority;
    this->type = none;
    switch(priority)
    {
        case init:RL = &(getManager()->initList);break;
        case system_:RL = &(getManager()->systemList);break;
        case user:RL = &(getManager()->userList);break;
    }
}

void PCB::KillTree()
{
    list<PCB*>::iterator iterp;
    for (iterp = children.begin();iterp != children.end();iterp++)
    {
        (*iterp)->KillTree();
    }
    map<RCB*,int>::iterator iter;
    for(iter = resources.begin(); iter != resources.end();iter++)
    {
        list<RCB*>::iterator iterr = (getManager()->resources).begin();
        RCB* r = (*iter).first;
        if(r == *iterr)
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

void PCB::Request(int rid)
{
    RCB* r = getManager()->FetchRCB(rid);
    if (r->status == 1)
    {
        r->status = 0;
        resources[r] = 1;
    }
    else
    {
        type = blocked;
        blockList = r;
        readyList = NULL;
        getManager()->RemoveProcess(priority,this);
        pair<PCB*,int> p(this,1);
        r->waitingList.push_back(p);
        getManager()->Scheduler();
    }

}

void PCB::Request(int rid,int n)
{
    RCB* r = getManager()->FetchRCB(rid);
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
            getManager()->Error(2);
            return;
        }
        type = blocked;
        blockList = r;
        readyList = NULL;
        getManager()->RemoveProcess(priority,this);
        pair<PCB* ,int> p(this,n);  
        r->waitingList.push_back(p);
        getManager()->Scheduler();
    }
}

void PCB::Release(int rid)
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
        list<pair<PCB*,int> >::iterator iterl = r->waitingList.begin();
        PCB* q = (*iterl).first;
        r->waitingList.erase(iterl);
        q->type = ready;
        q->readyList = RL;
        q->blockList = NULL;
        q->resources[r] = 1;
        q->readyList->push_back(q);
        getManager()->Scheduler();
    }
}

void PCB::Release(int rid,int n)
{
    RCB* r = getManager()->FetchRCB(rid);
    r->status = r->status+n;
    resources.erase(resources.find(r));
    list<pair<PCB*,int> >::iterator iter = r->waitingList.begin();
    while(r->waitingList.size() !=0 && r->status >= (*iter).second)
    {
        r->status = r->status - (*iter).second;
        PCB* q = (*iter).first;
        r->waitingList.erase((iter));
        q->type = ready;
        q->readyList = RL;
        q->blockList = NULL;
        if(q->resources.find(r) != q->resources.end())
        {
            int j = resources[r];
            resources[r] = j+n;
        }
        else
        {
            resources[r] = n;
        }
        q->readyList->push_back(q);
    }
    getManager()->Scheduler();
}

