#ifndef HEADER_RESOURCE
#define HEADER_RESOURCE

#include "process.h"
#include <string>
#include <list>
#include <map>
#include <utility>
//------------------------------
using std::string;
using std::list;
using std::map;
using std::pair;
//------------------------------
class PCB;
class RCB
{
    public:
        int RID;
        int status;
        string name;
        int k;
        list<pair<PCB*,int> > waitingList;
    public:
        RCB(int n,int i){status = n;RID = i; k = n;}
        void DeleteProcess(int PID);
        int getRID(){return this->RID;}
        void InsertProcess(PCB* pcb);
        int getStatus(){return status;}
        void setStatus(int status){this->status = status;}
        list<pair<PCB*,int> > & getWaitingList(){return waitingList;}
};
//------------------------------

#endif
