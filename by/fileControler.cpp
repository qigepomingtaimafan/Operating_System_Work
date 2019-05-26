#include<string>
#include<stdio.h>
-----------------------------------------------

FileControler::FileControler(const string inputFilePath,const string outputFilePath)
{
    inFile.open(inputFilePath);
    outFile.open(outputFilePath);
}

void FileControler::SetInputFilePath(const string inputFilePath)
{
    fclose(inFile);
    inFile.open(inputFilePath);
}

void FileControler::SetOutputFilePath(const string outputFilePath)
{
    fclose(outFile);
    outFile.open(outputFilePath);
}
