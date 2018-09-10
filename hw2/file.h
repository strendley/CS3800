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
        string m_fileTime;
    public:
        vector<string> m_filePermissions;

        //default constructor
        File();

        //getters
        string getName() {return m_fileName;}
        string getTime() {return m_fileTime;}

        void setTime()
        {
            time_t now = time(NULL);
            m_fileTime = ctime(&now);
        }

        //paramaterized constructor
        File(string nameOfFile)
        {
            m_fileName = nameOfFile;
            setTime();
            m_filePermissions.push_back("rwx");
            m_filePermissions.push_back("---");
            m_filePermissions.push_back("---");

        }

};




#endif
