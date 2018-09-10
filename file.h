#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <ctime>
#include <map>
#include <vector>
#include <string>
using namespace std;


class File 
{
    private:
        string m_fileName;
       

    public:
     vector<string> m_filePermissions;
        //default constructor
        File();

        //getters
        string getName() {return m_fileName;}
        vector<string> getPerms(){return m_filePermissions;}

        //paramaterized constructor
        File(string nameOfFile)
        {
            m_fileName = nameOfFile;
            time_t fileTime = time(NULL);
            string now = ctime(&fileTime);
            m_filePermissions.push_back("rwx");
            m_filePermissions.push_back("---");
            m_filePermissions.push_back("---");

        }

};




#endif
