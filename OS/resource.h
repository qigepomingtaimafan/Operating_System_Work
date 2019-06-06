#include "process.h"
#include <string>
#include <list>
#include <map>
//------------------------------
using std::string;
using std::list;
using std::map;
//------------------------------
typedef ResourceControlBlock RCB;
//------------------------------
class ResourceControlBlock
{
    public:
        int RID;
        int status;
        string name;
        int k;
        list<pair<PCB*,int> > waitingList;
    public:
        ResourceControlBlock(int n,int i){status = n;RID = i; k = n;}
        void DeleteProcess(int PID);
        int getRID(){return this->RID;}
        void InsertProcess(PCB* pcb);
        int getStatus(){return status;}
        void setStatus(int status){this->status = status;}
        list<PCB*> & getWaitingList(){return waitingList;}
}
