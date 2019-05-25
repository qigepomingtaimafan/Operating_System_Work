#include <iostream>
#include <fstream>
#include <string>

class FileControler
{
    private:
        static FileControler* fileControler;
        ifstream inFile;
        ofstream outFile;
    protected:
        FileControler (const string inputFilePath,const string outputFilePath);
        FileControler () {};
    public:
        static FileControler* getFileControler () {return fileControler;}
        SetInputFilePath (const string inputFilePath);
        SetOutputFilePath (const string outputFilePath);
        CloseInputFile ();
        CloseOutputFile ();
}
