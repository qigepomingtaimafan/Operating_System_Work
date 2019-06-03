#include "process.h"
#include "resource.h"
#include <list>
#include <queue>
#include <vector>
//------------------------------
using std::string;
using std::vector;
using std::list;
//------------------------------
class Manager
{
    private:
        list<PCB*> systemList;
        list<PCB*> userList;
        list<PCB*> initList;
        vector<RCB*> resources;
        vector<PCB*> processes;
        Manager();
        static Manager* manager;
        PCB* runningProcess;
    public:
        void CreateProcess(int PID,Priority priority);
        void DestroyProcess(int PID);
        void RemoveProcess(Priority priority,PCB* pcb);
        void InsertProcess(Priority priority,PCB* pcb);
        static Manager* getInstance();
        RCB* Get_RCB(int rid);
}
