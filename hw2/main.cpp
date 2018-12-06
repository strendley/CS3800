//Programmer: Skylar Trendley
//Professor: Dr. Wilkerson
//Purpose: Program functions as a linux shell.


#include <iostream>
#include <sstream>
#include <fstream>
#include "directory.h"
#include "memSim.h"
using namespace std;


int main()
{
    bool running = true;
    string cmd;
    directory dir;
    memorySim mem;

	cout << "~~~Welcome to the LinuxShell~~~" << endl;
	cout << "Supported commands:\n"
          "ls <-l>\n\tList contents of current directory (-l provides attribute details of contents)\n\n"
          "cd DIRECTORY_NAME\n\tChange current working directory\n\n"
          "pwd\n\tPrint the full path to the current working directory\n\n"
          "mkdir DIRECTORY_NAME\n\tMake a new directory in the current working directory\n\n"
          "rmdir DIRECTORY_NAME\n\tRemove a directory (and all its contents) from the current working directory\n\n"
          "rm FILE_NAME\n\tRemove a file from the current working directory\n\n"
          "chmod NUMERIC_PERMISSION_STRING FILE_OR_DIRECTORY_NAME\n\tChange the permissions on a file or directory in the current working directory\n\n"
          "touch FILE_NAME\n\tIf a file exists in the current working directory with the indicated name, update it's modification time, otherwise create it\n\n"
          "touch DIR_NAME\n\tUpdate the modification time of a directory in the current working directory\n\n"
          "exit\n\tQuit the shell emulator\n\n"
          "quit\n\tQuit the shell emulator\n\n" 
          "memload\n\tLoad a file to test the memory simulation\n\n" 
          "memstep <numsteps> or <all> \n\tstep through the memory simulation\n\n"
          "memalg <algorithm_name> \n\tselect the type of algorithm to test\n\n"
          "memview \n\tprint the memory block\n\n" << endl;
          

    while(running)
    {
        string flagOrFileName;
        string file;

       //output current directory
        //cout << dir.getDirName();

		cout << ">> ";

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
                    dir.printPerms();
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

            else if(cmd == "memreset")
            {
                mem.initVector(mem.getMemSize());
            }

            else if(cmd == "memset")
            {
                if (flagOrFileName.length() != 0)
                {
                    //use flagOrFileName to take in size in units
                    mem.setMemSize(stoi(flagOrFileName));
                    mem.initVector(mem.getMemSize());
                }
            }

            else if(cmd == "memload")
            {
                if (flagOrFileName.length() != 0)
                {
                    if(flagOrFileName == "traceOnly.txt")
                    {
                        if(mem.loadFile(flagOrFileName))
                        {
                            mem.setMemSize(1024);
                            mem.initVector(mem.getMemSize());
                            mem.storeData(mem.getFileContents(), 0);
                        }
                    }
                    else
                    {
                        if(mem.loadFile(flagOrFileName))
                        {
                            mem.setAlg(mem.getFileContents());
                            mem.setMemSizeFromFile(mem.getFileContents());
                            mem.initVector(mem.getMemSize());
                            mem.storeData(mem.getFileContents(), 2);
                        }

                        else
                        {   
                            cout << "Could not load file named " << flagOrFileName << "!" << endl;
                        }
                    }                
        
                }
            }      

            else if(cmd == "memstep")
            {
                if(flagOrFileName.length() != 0)
                {
                    if (flagOrFileName == "all")
                    {
                        int step = mem.getMaxSteps();
                        mem.AlgFit(step);     
                    }

                    else
                    {
                        int step = stoi(flagOrFileName);
                        mem.AlgFit(step);
                    }
                }
            }

            else if(cmd == "memview")
            {
                //ascii art of memview
                mem.printBlock();
            }

            else if(cmd == "memalg")
            {
                mem.setAlg(flagOrFileName);
            }

            else
            {
                //command doesn't match
                cout << "ERROR: " << cmd << " <- COMMAND NOT RECOGNIZED" << endl;
            }

    }
    return 0;
}