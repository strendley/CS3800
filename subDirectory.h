#ifndef SUBDIRECTORY_H
#define SUBDIRECTORY_H

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <string>
using namespace std;


class subDirectory 
{
    private:
        string m_subName;
        string m_subTime;
       // map 

    public:
        //default constructor
        subDirectory();

        //getters
        string getSubTime() {return m_subTime;}
        string getSubName() {return m_subName;}
        //string getPerms() {return m_filePermissions[1];}

        //paramaterized constructor
        subDirectory(string nameOfDir)
        {
            m_subName = nameOfDir;
            m_subTime = time(NULL);
            //m_filePermissions.push_back("rwx");
            //m_filePermissions.push_back("---");
            //m_filePermissions.push_back("---");

        }


};




#endif
