#include "process.h"
#include "resource.h"
#include <queue>
#include <vector>
//------------------------------
using std::string;
using std::vector;
//------------------------------
class Manager
{
    private:
        queue<PCB*> systemQueue;
        queue<PCB*> userQueue;
        queue<PCB*> initQueue;
        vector<RCB*> resources;
        vector<PCB*> processes;
        Manager();
        static Manager* manager;
    public:
        void CreateProcess(int PID,Priority priority);
        void DestroyProcess(int PID);
        void InsertProcess(Priority priority,PCB* pcb);
        static Manager* getInstance();
}
