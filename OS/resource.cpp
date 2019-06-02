#include <list>
#include "resource.h"
#include "process.h"
//--------------------------------
using std::list;
//--------------------------------
void ResourceControlBlock:DeleteProcess(int PID)
{
    list<PCB* >::iterator iter;
    for(iter = waitingList.begin();iter != waitingList.end();iter++)
    {
        if (*iter->getPID() == PID)
        {
            waitingList.erase(iter);    
        }
    }
}
