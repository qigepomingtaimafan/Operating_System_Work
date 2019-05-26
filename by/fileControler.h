#include <string>
#include <stdio.h>
---------------------------------------------------------
class FileControler
{
    private:
        static FileControler* fileControler;
        FILE* inFile;
        FILE* outFile;
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
