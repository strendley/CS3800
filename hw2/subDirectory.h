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
        vector<string> m_subPermissions;
        //default constructor
        subDirectory();

        //getters
        string getSubTime() {return m_subTime;}
        string getSubName() {return m_subName;}

        void setTime()
        {
            time_t now = time(NULL);
            m_subTime = ctime(&now);
        }

        //paramaterized constructor
        subDirectory(string nameOfDir)
        {
            m_subName = nameOfDir;
            setTime();
            m_subPermissions.push_back("---");
            m_subPermissions.push_back("---");
            m_subPermissions.push_back("rwx");
        }


};




#endif
