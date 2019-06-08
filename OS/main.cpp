#include <iostream>
#include <string>
#include "manager.h"
//-----------------------------------------------------
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
//-----------------------------------------------------
void FileFlow(Manager* manager);
void TerminalFlow(Manager* manager);
int main()
{
    string buf = "";
    Manager* manager = new Manager();
    cout<<"Shell Begin"<<endl;
    cout<<"Input q to exit"<<endl;
    cout<<"--------------------------------------"<<endl;
/*    while (1)
    {
        cout<<"-> ";
        cin>>buf;
        if(buf == "q")
        {
            cout<<"--------------------------------------"<<endl;
            cout<<"Shell Quit"<<endl;
            cout<<"--------------------------------------"<<endl;
            return 0;
        }
        if(manager->SwitchInOut(buf))
            break;
    }*/
    manager->terminal = false;
    if(manager->terminal)
    {
        TerminalFlow(manager);
        cout<<"--------------------------------------"<<endl;
        cout<<"Shell Quit"<<endl;
        cout<<"--------------------------------------"<<endl;
        return 0;
    }
    else 
    {
        FileFlow(manager);
        cout<<"--------------------------------------"<<endl;
        cout<<"Shell Quit"<<endl;
        cout<<"--------------------------------------"<<endl;
        return 0;
    }
    delete manager;
    return 0;
}

void FileFlow(Manager* manager)
{
    string buf;
    string buf1;
    string buf2;
    bool quit = false;
    int option = 0;
    manager->SwitchInOut("file");
    while(!quit)
    {
        buf = "";
        buf1 = "";
        buf2 = "";
        option = 0;
        manager->in>>buf;
        manager->line++;
        if(buf == "init")
            option = 1;
        else if(buf == "cr")
            option = 2;
        else if(buf == "list")
            option = 3;
        else if(buf == "to")
            option = 4;
        else if(buf == "req")
            option = 5;
        else if(buf == "de")
            option = 6;
        else if(buf == "q")
            option = 7;
        else if(buf == "\n")
            continue;
            
        switch(option)
        {
            case 1:
            {
                manager->Init();
                break;
            }
            case 2:
            {
                manager->in>>buf1>>buf2;
                if(buf1 == ""  || buf2 == "" )
                {    
                    manager->Error(3);
                    break;
                }
                switch (stoi(buf2))
                {
                    case 0: manager->Cr(buf1,init);break;
                    case 1: manager->Cr(buf1,user);break;
                    case 2: manager->Cr(buf1,system_);break;
                    default: manager->Error(3);break;
                }
                break;
            }
            case 3:
            {
                manager->in>>buf1;
                manager->List(buf1);
                break;
            }
            case 4:
            {
                manager->To();
                break;
            }
            case 5:
            {
                manager->in>>buf1>>buf2;
                if(buf1 =="" || buf2 == "")
                {
                    manager->Error(3);
                    break;
                }
                manager->Req(buf1,stoi(buf2));
                break;
            }
            case 6:
            {
                manager->in>>buf1;
                if(buf1 == "")
                {
                    manager->Error(3);
                    break;
                }
                manager->De(buf1);
                break;
            }
            case 7:
            {
                quit = true;
                break;
            }
            default:
            {
                manager->Error(3);
                break;
            }
        }
    }
}

void TerminalFlow(Manager* manager)
{
    string buf;
    string buf1;
    string buf2;
    bool quit = false;
    int option = 0;
    while(!quit)
    {
        buf = "";
        buf1 = "";
        buf2 = "";
        option = 0;
        cout<<"->";
        cin>>buf;
        
        if(buf == "init")
            option = 1;
        else if(buf == "cr")
            option = 2;
        else if(buf == "list")
            option = 3;
        else if(buf == "to")
            option = 4;
        else if(buf == "req")
            option = 5;
        else if(buf == "de")
            option = 6;
        else if(buf == "q")
            option = 7;
            
        switch(option)
        {
            case 1:
            {
                manager->Init();
                break;
            }
            case 2:
            {
                cin>>buf1>>buf2;
                if(buf1 == ""  || buf2 == "" )
                {    
                    manager->Error(3);
                    break;
                }
                switch (stoi(buf2))
                {
                    case 0: manager->Cr(buf1,init);break;
                    case 1: manager->Cr(buf1,user);break;
                    case 2: manager->Cr(buf1,system_);break;
                    default: manager->Error(3);break;
                }
                break;
            }
            case 3:
            {
                cin>>buf1;
                manager->List(buf1);
                break;
            }
            case 4:
            {
                manager->To();
                break;
            }
            case 5:
            {
                cin>>buf1>>buf2;
                if(buf1 =="" || buf2 == "")
                {
                    manager->Error(3);
                    break;
                }
                manager->Req(buf1,stoi(buf2));
                break;
            }
            case 6:
            {
                cin>>buf1;
                if(buf1 == "")
                {
                    manager->Error(3);
                    break;
                }
                manager->De(buf1);
                break;
            }
            case 7:
            {
                quit = true;
                break;
            }
            default:
            {
                manager->Error(3);
                break;
            }
        }
        cout<<endl;
    }
}
