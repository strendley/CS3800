//

#include "memSim.h"
using namespace std;
#include <iostream>

    void memorySim::storeData(vector<string> fileContents, int start)
    {
        for (unsigned int i = start; i < fileContents.size()-1; i++)
        {
            data.push_back(fileContents[i]);
        }
    }

    void memorySim::initVector(int size)
    {
        memoryBlock.clear();
        for (int i = 0; i < size; i++)
        {
            memoryBlock.push_back("*");
        }
    }

    int memorySim::getMaxSteps()
    {
        int initStart = atoi(data.at(0).c_str());
        int initFinish = atoi(data.at(2).c_str());
        int maxTime = initStart + initFinish;

        for (unsigned int i = 0; i < data.size()-3; i+=3)
        {
            int start_time = atoi(data.at(i).c_str());
            int finish_time = atoi(data.at(i+2).c_str());
            int total_time = start_time + finish_time;

            if (maxTime < total_time)
                maxTime = total_time;
        }

        return maxTime;
    }


    bool memorySim::loadFile(string fileName)
    {
        string contents;
        ifstream myFile;

        myFile.open(fileName);
        if(myFile.is_open())
        {
            while(myFile >> contents)
            {
                fileContents.push_back(contents);
            }

            myFile.close();
            return true;
        }

        else
        {
            return false;
        }
    }

    void memorySim::clearBlock(int timeStep)
    {
        for (unsigned int i = 0; i < memoryBlock.size()-1; i++)
        {
            if (atoi(memoryBlock.at(i).c_str()) == timeStep)
                memoryBlock[i] = "*";
        }
    }

    void memorySim::printBlock()
    {
        cout << "|";
        for (unsigned int i = 0; i < this->memoryBlock.size()-1; i++)
        {
            cout << " " << this->memoryBlock[i] << " |";
        }

        cout << endl << endl;
    }

    void memorySim::AlgFit(int numSteps)
    {
        int curr_time  = 0;
        int start_time = 0;
        int process_size = 0;
        int finish_time = 0;

        for(int i = 0; i <= numSteps; i++)
        {
            cout << "Current Step: " << i << endl;
            curr_time = i;

            clearBlock(i);

           for(unsigned int j = 0; j < this->data.size()-3; j+=3)
           {

                start_time = atoi(data.at(j).c_str());
                process_size = atoi(data.at(j+1).c_str());
                finish_time = atoi(data.at(j+2).c_str());

                if(start_time == curr_time)
                {
                    if (getAlg() == 1)
                    {
                        if(!insertDataFirst(process_size, finish_time, curr_time))
                        {
                            cout << "ERROR FIRST --- Not enough memory to insert the block!" << endl;
                        }
                    }

                    if (getAlg() == 2)
                    {
                        if(!insertDataNext(process_size, finish_time, curr_time))
                        {
                            hasHitEnd = false;
                            cout << "ERROR NEXT --- Not enough memory to insert the block!" << endl;
                        }
                    }

                    if (getAlg() == 3)
                    {
                        if(!insertDataBest(process_size, finish_time, curr_time))
                        {
                            cout << "ERROR BEST --- Not enough memory to insert the block!" << endl;
                        }
                    }
                }
           }

            printBlock();
        }//end for loop
    }//end function

bool memorySim::insertDataFirst(int process_size,int finish_time,int curr_time)
{
    int start_pos = 0;
    int finish_pos = 0;
    for(int i = 0; i < this->getMemSize()-1; i++)
    {
        if(this->memoryBlock[i] == "*")
        {
            start_pos = i;
            while( i < this->memoryBlock.size()-1 && this->memoryBlock[i] == "*")
            {
                finish_pos = i;
                if(finish_pos - start_pos == process_size)
                {
                    insertIntoMemory(start_pos, finish_pos, curr_time, finish_time);
                    return true;
                }
                i++;
            }
        }
    }
    return false;
}

bool memorySim::insertDataNext(int process_size, int finish_time, int curr_time)
{
    int start_pos = 0;
    int finish_pos = 0;

    for(int i = lastPos; i < this->getMemSize()-1; i++)
    {
        if(this->memoryBlock[i] == "*")
        {
            start_pos = i;
            while( i < this->memoryBlock.size()-1 && this->memoryBlock[i] == "*")
            {
                finish_pos = i;     
                if(finish_pos - start_pos == process_size)
                {
                    insertIntoMemory(start_pos, finish_pos, curr_time, finish_time);
                    return true;
                }
                i++;
                lastPos = i;
            }
        }
    }

    if (lastPos == this->getMemSize()-1 && hasHitEnd == false)
    {
        lastPos = 0;
        hasHitEnd = true;
        insertDataNext(process_size, finish_time, curr_time);
    }

    return false;

}

bool memorySim::insertDataBest(int process_size, int finish_time, int curr_time)
{
    int start_pos = 0;
    int finish_pos = 0;
    int openLength = 0;
    vector<tuple<int, int, int>> possiblePositions;

    for(int i = 0; i < this->getMemSize()-1; i++)
    {
        if(this->memoryBlock[i] == "*")
        {
            start_pos = i;
            while( i < this->memoryBlock.size()-1 && this->memoryBlock[i] == "*")
            {
                finish_pos = i;
                openLength++;
                i++;
            }

            if (openLength == process_size)
            {
                insertIntoMemory(start_pos, finish_pos, curr_time, finish_time);
                return true;
            }

            else if (openLength > process_size)
            {
                possiblePositions.push_back(make_tuple(openLength, start_pos, finish_pos));
            }
            
        }

        if(i == this->getMemSize()-1)
        {
            tuple<int,int,int> bestSpace;
            bestSpace = selectBest(possiblePositions);
            int finishingPos = get<1>(bestSpace) + process_size;
            insertIntoMemory(get<1>(bestSpace), finishingPos, curr_time, finish_time);

            return true;
        }
    }
    return false;
}

tuple<int,int, int> memorySim::selectBest(vector<tuple<int, int, int>> possiblePositions)
{
    sort(possiblePositions.begin(), possiblePositions.end());
    return possiblePositions[0];
}


void memorySim::insertIntoMemory(int start_pos, int finish_pos, int curr_time, int finish_time)
{

    for (int i = start_pos; i < finish_pos; i++)
    {
        this->memoryBlock[i] = to_string(finish_time + curr_time);
    }
}