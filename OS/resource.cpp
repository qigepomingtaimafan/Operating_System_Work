#include <list>
#include "resource.h"
#include "process.h"
//--------------------------------
using std::list;
//--------------------------------
void RCB::DeleteProcess(int PID)
{
    list<pair<PCB*,int> >::iterator iter;
    for(iter = waitingList.begin();iter != waitingList.end();iter++)
    {
        pair<PCB*,int> p = *iter;
        if (p.first->PID == PID)
        {
            waitingList.erase(iter);    
        }
    }
}

/*void RCB::InsertProcess(PCB* pcb)
{
    waitingList.push_back());
}
*/
