#include <iostream>
#include <string>
#include "manager.h"
//-----------------------------------------------------
using std::string;
using std::cout;
using std::cin;
using std::endl;
//-----------------------------------------------------
int main()
{
    string buf = "";
    Manager* manager = new Manager();
    cout<<"Shell Begin"<<endl;
    cout<<"Input q to exit"<<endl;
    cout<<"--------------------------------------"<<endl;
    while (1)
    {
        cout<<"-> ";
        cin>>buf;
        if(buf == "q")
        {
            cout<<"Shell Quit"<<endl;
            return 0;
        }
        manager->SwitchInOut(buf);
    }

    delete manager;
    return 0;
}
