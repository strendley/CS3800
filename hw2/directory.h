#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <map>
#include <vector>
#include "file.h"
#include "subDirectory.h"
using namespace std;

class directory
{
    private:
    string currentDir;
    map <string,pair<vector<File>,vector<subDirectory>>> directoryItems;

    public:

    //default constructor
    directory()
    {
        setDirName();
        directoryItems[currentDir].first.push_back(File("file.txt"));
        directoryItems[currentDir].second.push_back(subDirectory("dir"));
    }


    //get directory items
    vector<File> getFiles() {return directoryItems[currentDir].first;}
    vector<subDirectory> getSubDirs() {return directoryItems[currentDir].second;}
    string getDirName() {return currentDir;}

    //set up directory items
    void setDirName()
    {
        currentDir = "shell/";
    }

    void setDirName(string dirName)
    {
        currentDir = currentDir + dirName + "/";
    }

    //add the file to the map
    void addFiles(vector<File> files)
    {
        directoryItems[currentDir].first = files;
    }

    //add the subdirectory to the map
    void addSubDirectories(vector<subDirectory> subDirs)
    {
        directoryItems[currentDir].second = subDirs;
    }

    //make a new directory
    void makeDirectory(string dirName);

    //make a new file
    void makeFile(string fileName);

    //remove a file
    void removeFile(string fileName);

    //remove a directory
    void removeDirectory(string dirName);

    //print the current directory's contents
    void printDirectoryContents();
    //print the current directory's contents with permissions
    void printDirectoryContents(string val);

    //print the directory path
    void printWorkingDirectory();

    //change to previous directory
    void changeDirectory();
    //change to chosen directory
    void changeDirectory(string dirName);
    
    //print the permissions of the files
    void printFilePerms();
    
    //alter the permissions of the directory
    void newPerms(string flag, string fileName);




};






















#endif
