#include "resource.h"
#include "manager.h"
#include "process.h"
#include "priority.h"
#include <list>
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
//--------------------------------
using std::list;
using std::map;
using std::pair;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
//--------------------------------
void Manager::PrintString(string s)
{
    if(terminal)
    {
        cout<<s;
        cout<<"--------------------------------------"<<endl;
    }
    else
    {
        out<<"Line "<<std::to_string(line)<<":"<<endl;
        out<<s;
        out<<"--------------------------------------"<<endl;
    }
}

void Manager::DestroyProcess(int PID)
{
    PCB* p = FetchPCB(PID);
    if(p != NULL)
    {
        p->KillTree();
        list<PCB*>::iterator iter = processes.begin();
        for(;iter != processes.end();iter++)
        {
            if((*iter) == p)
            {
                processes.erase(iter);
                break;
            }
        }
    }
    else
    {
        Error(1);
    }
    Scheduler();
}

PCB* Manager::CreateProcess(int PID,Priority priority,string name)
{
    PCB* pcb = new PCB(PID,priority);
    pcb->parent = runningProcess;
    pcb->name = name;
    pcb->setManager(this);
    processes.push_back(pcb);
    if(priority != init)
        runningProcess->children.push_back(pcb);
    switch(priority)
    {
        case init:
        {
            initList.push_back(pcb);
            pcb->RL = &initList;
            break;
        }
        case system_:
        {
            systemList.push_back(pcb);
            pcb->RL = &systemList;
            break;
        }
        case user:
        {
            userList.push_back(pcb);
            pcb->RL = &userList;
            break;
        }
    }
    Scheduler();
    return pcb;
}

void Manager::RemoveProcess(Priority priority,PCB* pcb)
{
    list<PCB*> * l;
    switch(priority)
    {
        case init:
        {
            l = &initList;
            break;
        }
        case system_:
        {
            l = &systemList;
            break;
        }
        case user:
        {
            l = &userList;
            break;
        }
    }
    list<PCB*>::iterator iter;
    for (iter = l->begin();iter != l->end();iter++)
    {
        if (*iter == pcb)
        {
            l->erase(iter);
            return ;
        }
    }
}

PCB* Manager::FetchPCB(int pid)
{
    list<PCB*>::iterator iter;
    for(iter = processes.begin(); iter != processes.end();iter++)
    {
        if((*iter)->PID == pid)
        {
            return *iter;
        }

    }
    return NULL;
}

PCB* Manager::FetchPCB(string name)
{
    list<PCB*>::iterator iter;
    for(iter = processes.begin(); iter != processes.end();iter++)
    {
        if((*iter)->name == name)
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
        if((*iter)->RID == rid)
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
        if((*iter)->name == name)
        {
            return *iter;
        }

    }
    return NULL;
}

void Manager::InsertProcess(Priority priority,PCB* pcb)
{
    
    list<PCB*> * l;
    switch(priority)
    {
        case init:
        {
            l = &initList;
            break;
        }
        case system_:
        {
            l = &systemList;
            break;
        }
        case user:
        {
            l = &userList;
            break;
        }
    }
    l->push_back(pcb);
}

void Manager::Init()
{
    PCB* initTmp = CreateProcess(0,init,"init");
    for (int i =0;i<4;i++)
    {
        RCB* tmp = new RCB(i+1,i+1);
        int n = i+1;
        tmp->name = "R" + std::to_string(n);
        resources.push_back(tmp);
    }
    processes.push_back(initTmp);
}
void Manager::Cr(string x,Priority priority)
{
    PCB* run = runningProcess;
    CreateProcess(processes.size(),priority,x);
    string buf = "process " + runningProcess->name + " is running\n";
    if(run->PID == runningProcess->PID)
        PrintString(buf);
}

void Manager::List(string option)
{
    string buf = "";
    if(option == "ready")
    {
        list<PCB*>::iterator iter;
        buf += "2:"; 
        for(iter = systemList.begin();iter != systemList.end();iter++)
        {
            if(iter != systemList.begin())
                buf += "--";
            buf += (*iter)->name;
        }
        buf += "\n";
        buf += "1:";
        for(iter = userList.begin();iter != userList.end();iter++)
        {
            if(iter != userList.begin())
                buf += "--";
            buf += (*iter)->name;
        }
        buf += "\n";
        buf += "0:init";
        for(iter = initList.begin();iter != initList.end();iter++)
        {
            if(iter != initList.begin())
                buf += "--";
            buf += (*iter)->name;
        }
        buf += "\n";
    }
    else if(option == "res")
    {
        list<RCB*>::iterator iter;
        for(iter = resources.begin();iter != resources.end();iter++)
        {
            buf = buf + (*iter)->name +"  " + std::to_string((*iter)->status)+ "\n";
        }
    
    }
    else if(option == "block")
    {
        list<RCB*>::iterator iter;
        for(iter = resources.begin();iter != resources.end();iter++)
        {
            buf += (*iter)->name;
            buf += " ";
            list<pair<PCB*,int> >::iterator iterp;
            for(iterp = (*iter)->waitingList.begin();iterp != (*iter)->waitingList.end();iterp++)
            {
                buf += (*iterp).first->name;
                buf += " ";
            }
            buf += "\n";
        }
    }
    else
    {
        buf = buf += "Invalid word after \"list\"\n";
    }
    PrintString(buf);
}

void Manager::To()
{
    Time_out();
}

void Manager::Req(string name,int n)
{
    string buf = "";
    if(runningProcess->Request(FetchRCB(name)->RID,n))
    {
        buf = buf + "process "+ runningProcess->name + " requests " + std::to_string(n) +" " +name + "\n";
        PrintString(buf);
    }
}

void Manager::De(string name)
{
    string buf = "";
    PCB* pcb = FetchPCB(name);
    map<RCB*,int>::iterator iter;
    for(iter = pcb->resources.begin();iter != pcb->resources.end();iter++)
    {
        buf += "release " + (*iter).first->name + "\n";
    }
    DestroyProcess(pcb->PID);
    PrintString(buf);
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
        if(pcb && pcb != p) 
        {
            pcb->type = ready;
        }
    }
}

void Manager::Preempt(PCB* p)
{
    p->type = running;
    string buf = "";
    buf = "process " + p->name + " is running\n";
    runningProcess = p;
    RemoveProcess(p->priority,p);
    PrintString(buf);
}

void Manager::Time_out()
{
    PCB* q = runningProcess;
    RemoveProcess(q->priority,q);
    q->type = ready;
    InsertProcess(q->priority,q);
    Scheduler();
    if(q != runningProcess)
    {
        string buf = "";
        buf = "process " + q->name + " is ready" + "\n";
        PrintString(buf);
    }
}

bool Manager::SwitchInOut(string option)
{
    if(option == "file")
    {
        terminal = false;
        in.open("in.txt",std::ios::in);
        if(!in.is_open())
        {
            cout<<"--------------------------------------"<<endl;
            cout<<"File in.txt is not exist or no permisson."<<endl;
            cout<<"--------------------------------------"<<endl;
            return false;
        }
        out.open("out.txt",std::ios::out);
        cout<<"File I/O mode.Input at in.txt.Output at out.txt"<<endl;
        cout<<"--------------------------------------"<<endl;
        return true;
    }
    else if(option == "terminal")
    {
        terminal = true;
        cout<<"--------------------------------------"<<endl;
        cout<<"Terminal I/O mode.Input and output will be fromterminal"<<endl;
        cout<<"--------------------------------------"<<endl;
        return true;
    }
    else 
    {
        cout<<"--------------------------------------"<<endl;
        cout<<"Please input vaild word : file or terminal"<<endl;
        cout<<"--------------------------------------"<<endl;
        return false;
    }
}

void Manager::Error(int n)
{
    string buf;
    switch(n)
    {
        case 2:
        {
            buf += "beyond the resource num\n";
            PrintString(buf);
            break;
        }
        case 3:
        {
            buf += "Iligal command\n";
            PrintString(buf);
            break;
        }
    }
}
