#include "resource.h"
#include "manager.h"
#include "process.h"
#include <list>
#include <map>
#include <pair>
#include <string>
#include <iostream>
#include <fstream>
//--------------------------------
using std::list;
using std::map;
using std::pair;
using std::string;
using std::ios::ifsteam;
using std::ios::ofstream;
using std::cout;
using std::cin;
//--------------------------------
Manager* Manager::getManager()
{
    if(manager == NULL)
    {
        manager = new Manager();
    }
    return manager;
}

void Manager::DestroyProcess(int PID)
{
    PCB* P = FetchPCB(PID);
    if(p != NULL)
    {
        p->Kill_Tree();
        processes.erase(processes.find(p));
    }
    else
    {
        Error(1);
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

PCB* Manager::CreateProcess(int PID,Priority priority)
{
    PCB* pcb = new PCB(PID,priority);
    pcb->parent = runningProcess;
    pcb->setManager(this);
    runningProcess->children.push_back(pcb);
    switch(priority)
    {
        case init:
        {
            initList.push_back(pcb);
            pcb->RL = initList;
            break;
        }
        case system:
        {
            systemList.push_back(pcb);
            pcb->RL = systemList;
            break;
        }
        case user:
        {
            userList.push_back(pcb);
            pcb->RL = userList;
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

PCB* Manager::FetchPCB(int pid)
{
    list<PCB*>::iterator iter;
    for(iter = processes.begin(); iter != processes.end();iter++)
    {
        if(*iter->PID == pid)
        {
            return *iter;
        }

    }
    return NULL;
}

RCB* Manager::FetchRCB(int rid)
{
    list<RCB*>::iterator iter;
    for(iter = resources.begin(); iter != resources.end();iter++)
    {
        if(*iter->RID == rid)
        {
            return *iter;
        }

    }
    return NULL;
}


RCB* Manager::FetchRCB(string name)
{
    list<RCB*>::iterator iter;
    for(iter = resources.begin(); iter != resources.end();iter++)
    {
        if(*iter->name == name)
        {
            return *iter;
        }

    }
    return NULL;
}

void Manager::InsertProcess(Priority priority,PCB* pcb)
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
    l.push_back(pcb);
}

void Manager::Init()
{
    PCB* initTmp = CreateProcess(0,init);
    initTmp->name = "init";
    for (int i =0;i<4;i++)
    {
        RCB* tmp = new RCB(i+1,i+1);
        int n = i+1;
        tmp->name = "R" + std::to_string(n);
        sources.push_back(tmp);
    }
}
void Manager::Cr(string x,Priority priority)
{
    CreateProcess(processes.size(),priority);
}

void Manager::List(string option);
{
    if(option == "ready")
    {
        PrintLineNum();
        *out<<"2: ";
        list<PCB*>::iterator iter;
        for(iter = systemList.begin();iter != systemList.end();iter++)
        {
            if(iter != systemList.begin())
                *out<<"--"
            *out<<*iter->name;
        }
        *out<<endl;
        *out<<"\t1:";
        for(iter = userList.begin();iter != userList.end();iter++)
        {
            if(iter != userList.begin())
                *out<<"--"
            *out<<*iter->name;
        }
        *out<<endl;
        *out<<"\t0:";
        for(iter = initList.begin();iter != initList.end();iter++)
        {
            if(iter != initList.begin())
                *out<<"--"
            *out<<*iter->name;
        }
        *out<<endl;
    }
    else if(option == "res")
    {
        PrintLineNum();
        list<RCB*>::iterator iter;
        for(iter = resources.begin();iter != resources.end();iter++)
        {
            if(iter != resource.begin())
                *out<<"\t";
            *out<<*iter->name<<"  "<<*iter->status<<endl;
        }
    
    }
    else if(option == "block")
    {
        PrintLineNum();
        list<RCB*>::iterator iter;
        for(iter = resources.begin();iter != resources.end();iter++)
        {
            if (iter != resources.begin())
                *out<<"\t";
            *out<<*iter->name<<" ";
            list<pair<PCB*,int> >::iterator iterp;
            for(iterp = *iter->waitingList.begin();iterp != *iter->waitingList.end();iterp++)
            {
                *out<<*iterp.first->name<<" ";
            }
            *out<<endl;
        }
    }
    else
    {
        PrintLineNum();
        *cout<<"Invalid word after \"list\""<<option<<endl;
    }
}

void To()
{
    Time_out();
}

void Req(string name,int n)
{
    runningProcess(FetchRCB(name)->RID,n);
    PrintLineNum();
    *out<<"process "<<runningProcess->name<<"requests "<<n<<" "<<name<<endl;
}

void De(string name)
{
    PrintLineNum();
    *out<<"release "<<releaseName<<" .wake up process"<<runningProcess->name<<endl;
}

void PrintLineNum()
{
    *out<<"("<<line<<")"<<"\t";    
}


void Manager::Scheduler()
{
    PCB* p;
    PCB* pcb = runningProcess;
    if (systemList.size() == 0)
    {
        if (userList.size() == 0)
        {
            if (initList.size() == 0)
            {
                p = NULL;
                return;
            }
            else
            {
                p = *(initList.begin());
            }
        }
        else
        {
            p = *(userList.begin());
        }
    }
    else
    {
        p = *(systemList.begin());
    }
    if ( pcb == NULL || pcb->priority < p->priority || pcb->type != running )
    {
        Preempt(p);
    }
}

void Manager::Preempt(PCB* p)
{
    P->status = running;
    PrintLineNum();
    *out<<"process "<<p->name<<" is running,";
}

void Manager::Time_out()
{
    PCB* q = runningProcess;
    RemoveProcess(q->priority,q);
    q->type = ready;
    InsertProcess(q->priority,q);
    Scheduler();
    *out<<", process "<<q->name <<"is ready"<<endl;
}

void Manager::SwitchInOut(string option)
{
    if(option == "file")
    {
        ofstream* o = new ofsteam();
        out = o;
        ifstream* i = new ifsteam();
        in = i;
        cout<<"File I\/O mode.Input at in.txt.Output at out.txt"<<endl;
    }
    else if(option == "terminal")
    {
        cout* o = new cout();
        out = o;
        cin* i = new cin();
        in = i;
        cout<<"Terminal I\/O mode.Input and output will be fromterminal"<<endl;
    }
}
