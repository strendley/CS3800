//Programmer: Skylar Trendley
//Professor: Dr. Wilkerson
//Purpose: Program functions as a linux shell.


#include <iostream>
#include <sstream>
#include "directory.h"
using namespace std;


int main()
{
    bool running = true;
    string cmd;
    directory dir;

    while(running)
    {
        string flagOrFileName;
        string file;
        
       //output current directory
        cout << dir.getDirName();

        //get the command from the terminal
        getline(cin, cmd);

        //parse each string in the stream for the command and flags
        istringstream iss(cmd);
        iss >> cmd >> flagOrFileName >> file;

            if(cmd == "ls")
            {
                if(flagOrFileName == "-l")
                {
                    //output directory contents with permissions
                    dir.printFilePerms();
                }

                else if(flagOrFileName == "")
                {
                    //output directory contents without permissions
                    dir.printDirectoryContents();
                }

                else
                {
                    //flag doesn't match
                    cout << "ERROR: " << flagOrFileName << " <- FLAG DOES NOT EXIST" << endl;
                }
            }

            else if(cmd == "pwd")
            {
                dir.printWorkingDirectory();
                
            }

            else if(cmd == "cd")
            {
                if(flagOrFileName == "..")
                {
                    //go up one directory
                    dir.changeDirectory();
                }

                //if(flagOrFileName != "..")
                else
                {
                    dir.changeDirectory(flagOrFileName);
                }
                
            }

            else if(cmd == "chmod")
            {
                //change the permissions granted to user
                dir.newPerms(flagOrFileName, file);
            }

            else if(cmd == "mkdir")
            {
                //make a new directory
                dir.makeDirectory(flagOrFileName);
            }
            
            else if(cmd == "rm")
            {
                //remove a directory
                dir.removeFile(flagOrFileName);
            }

            else if(cmd == "rmdir")
            {
                //remove a directory
                dir.removeDirectory(flagOrFileName);
            }

            else if(cmd == "touch")
            {
                //make a new file
                dir.makeFile(flagOrFileName);
            }

                
            else if(cmd == "exit" || cmd == "quit")
            {
                //stop looping for instructions
                running = false;
            }

            else
            {
                //command doesn't match
                cout << "ERROR: " << cmd << " <- COMMAND NOT RECOGNIZED" << endl;
            }

    }
    return 0;
}