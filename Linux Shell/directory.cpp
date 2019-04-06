#include "directory.h"
#include <string>
#include <cstddef>
#include <cstdlib>

void directory::printDirectoryContents()
{
    //loop through the files to print
    vector<File> filesInDir = this->getFiles();
    for(unsigned int i = 0; i < filesInDir.size(); i++)
    {
        cout << filesInDir[i].getName() << " ";
    }

    //loop through the subdirectories to print
    vector<subDirectory> SubDirsInDir = this->getSubDirs();
    for(unsigned int i = 0; i < SubDirsInDir.size(); i++)
    {
        cout << SubDirsInDir[i].getSubName() << " ";
    }

    cout << endl;
}

void directory::printWorkingDirectory()
{
    cout << currentDir << endl;
}

void directory::changeDirectory()
{
    if(currentDir == "shell/")
    {
        cout << "ERROR: CANNOT GO PAST DEFAULT DIRECTORY" << endl;
    }

    else
    {
        //loop through twice to find the previous directory, then split the string
        for(int i = 0; i < 2; i++)
        {
            string newDir = currentDir;
            size_t lastDir = newDir.find_last_of("/");
            currentDir = newDir.substr(0,lastDir);
        }

        //re-add the / onto the directory
        currentDir = currentDir + "/";
    }
    
}

void directory::changeDirectory(string dirName)
{
    vector<subDirectory> SubDirsInDir = this->getSubDirs();

     //loop through the subdirectories to find the target directory
    for(unsigned int i = 0; i < SubDirsInDir.size(); i++)
    {
        //if the directory exists, change the directory path
        if(dirName == SubDirsInDir[i].getSubName())
        {
            setDirName(dirName);
            return;
        }       
    }
    //if it doesn't, show the error
    cout << "ERROR: DIRECTORY DOES NOT EXIST" << endl;  
    
}

void directory::makeDirectory(string dirName)
{
    vector<subDirectory> subDirs = this->getSubDirs();

    //add the directory to the map
    this->addSubDirectories(subDirs);
    directoryItems[currentDir].second.push_back(subDirectory(dirName));
    
}

void directory::makeFile(string fileName)
{
    vector<File> subFiles = this->getFiles();

    //add the file to the map
    this->addFiles(subFiles);
    directoryItems[currentDir].first.push_back(File(fileName));
    
}

void directory::removeFile(string fileName)
{
    vector<File> filesInDir = this->getFiles();
    bool foundFile = false;

    for(unsigned int i = 0; i < filesInDir.size(); i++)
    {
        //if the file exists, erase the directory path
        if(fileName == filesInDir[i].getName())
        {
            filesInDir.erase(filesInDir.end() - i);
            foundFile = true;
        }
    }
    if(foundFile == false)
    {
         //if the file was not found, tell the user it did not exist
        cout << "ERROR: COULD NOT DELETE FILE -> '" << fileName << "' DOES NOT EXIST"  << endl;
    }
    else
    {
        //update the file vector
        this->addFiles(filesInDir);
    }
}

void directory::removeDirectory(string dirName)
{
    vector<subDirectory> subDirs = this->getSubDirs();
    bool foundDir = false;

    for(unsigned int i = 0; i < subDirs.size(); i++)
    {
        //if the directory exists, erase the directory path
        if(dirName == subDirs[i].getSubName())
        {
            subDirs.erase(subDirs.end() - i);
            foundDir = true;
        }
    }

    if(foundDir == false)
    {
        //if the subdirectory was not found, tell the user it did not exist
        cout << "ERROR: COULD NOT DELETE DIRECTORY -> '" << dirName << "' DOES NOT EXIST"  << endl;
    }
    else
    {
        //update the directory vector
        this->addSubDirectories(subDirs);
    }
}

void directory::printPerms()
{
    //loop through the file directory to print the name & perms of each file
    vector<File> filesInDir = this->getFiles();
    for(unsigned int i = 0; i < filesInDir.size(); i++)
    {
        cout << filesInDir[i].getName() << " | ";
        for(unsigned int j = 0; j < filesInDir[i].m_filePermissions[i].size(); j++)
        {
            cout << filesInDir[i].m_filePermissions[j];
        }
        cout << " | " << filesInDir[i].getTime();
    }

    vector<subDirectory> subDirs = this->getSubDirs();
    for(unsigned int i = 0; i < subDirs.size(); i++)
    {
        cout << subDirs[i].getSubName() << " | ";
        for(unsigned int j = 0; j < subDirs[i].m_subPermissions[i].size(); j++)
        {
            cout << subDirs[i].m_subPermissions[j];
        }
        cout << " | " << subDirs[i].getSubTime();
    }
}

void directory::newPerms(string flag, string name)
{
    
    bool found = false;
    int permissionVal;
    int pos;

    vector<File> filesInDir = this->getFiles();
    for(unsigned int i = 0; i < filesInDir.size(); i++)
    {
        //check first to see if the file exists
        if(name == filesInDir[i].getName())
        {
            found = true;

            //update last changed time
            this->directoryItems[this->currentDir].first[i].setTime();

            pos = i;
            for(unsigned int j = 0; j < flag.length(); j++)
            {

                permissionVal = flag[j] - 48;

                switch(permissionVal)
                {
                    case 0:
                    {
                        filesInDir[i].m_filePermissions[j]="---";
                    }
                    break;

                    case 1:
                    {
                       filesInDir[i].m_filePermissions[j]="--x";
                    }
                    break;

                    case 2:
                    {
                        filesInDir[i].m_filePermissions[j]="-w-";
                    }
                    break;

                    case 3:
                    {
                         filesInDir[i].m_filePermissions[j]="-wx";
                    }
                    break;

                    case 4:
                    {
                         filesInDir[i].m_filePermissions[j]="r--";
                    }
                    break;
                    
                    case 5:
                    {
                         filesInDir[i].m_filePermissions[j]="r-x";
                    }
                    break;

                    case 6:
                    {
                        filesInDir[i].m_filePermissions[j]="rw-";
                    }
                    break;

                    case 7:
                    {
                         filesInDir[i].m_filePermissions[j]="rwx";
                    }
                    break;

                    default:
                    {

                        cout << "ERROR: PERMISSION NOT RECOGNIZED" << endl;
                        return;
                    }


                }
            }

        this->directoryItems[this->currentDir].first[pos].m_filePermissions = filesInDir[pos].m_filePermissions;

        return;


        }
    }

    vector<subDirectory> subDirs = this->getSubDirs();
    for(unsigned int i = 0; i < subDirs.size(); i++)
    {
        //check first to see if the file exists
        if(name == subDirs[i].getSubName())
        {
            found = true;

            //update last changed time
            this->directoryItems[this->currentDir].second[i].setTime();

            pos = i;
            for(unsigned int j = 0; j < flag.length(); j++)
            {

                permissionVal = flag[j] - 48;

                switch(permissionVal)
                {
                    case 0:
                    {
                        subDirs[i].m_subPermissions[j]="---";
                    }
                    break;

                    case 1:
                    {
                       subDirs[i].m_subPermissions[j]="--x";
                    }
                    break;

                    case 2:
                    {
                        subDirs[i].m_subPermissions[j]="-w-";
                    }
                    break;

                    case 3:
                    {
                        subDirs[i].m_subPermissions[j]="-wx";
                    }
                    break;

                    case 4:
                    {
                        subDirs[i].m_subPermissions[j]="r--";
                    }
                    break;
                    
                    case 5:
                    {
                        subDirs[i].m_subPermissions[j]="r-x";
                    }
                    break;

                    case 6:
                    {
                        subDirs[i].m_subPermissions[j]="rw-";
                    }
                    break;

                    case 7:
                    {
                        subDirs[i].m_subPermissions[j]="rwx";
                    }
                    break;

                    default:
                    {
                        cout << "ERROR: PERMISSION NOT RECOGNIZED" << endl;
                        return;
                    }


                }
            }

        this->directoryItems[this->currentDir].second[pos].m_subPermissions = subDirs[pos].m_subPermissions;

        return;


        }
    }

    //if it does not, return back to the prompt
    if(found == false)
    {
         //if the file was not found, tell the user it did not exist
        cout << "ERROR: COULD NOT MODIFY FILE -> '" << name << "' DOES NOT EXIST"  << endl;
        return;
    }
}
