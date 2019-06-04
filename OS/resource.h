#include "process.h"
#include <string>
#include <list>
//------------------------------
using std::string;
using std::list;
//------------------------------
typedef ResourceControlBlock RCB;
//------------------------------
class ResourceControlBlock
{
    private:
        int RID;
        int status;
        list<PCB*> waitingList;
    public:
        ResourceControlBlock(int n,int i){status = n;RID = i;}
        void DeleteProcess(int PID);
        int getRID(){return this->RID;}
        void InsertProcess(PCB* pcb);
        int getStatus(){return status;}
        void setStatus(int status){this->status = status;}
}
