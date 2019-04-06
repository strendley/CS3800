#ifndef MEMSIM_H
#define MEMSIM_H


using namespace std;
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <algorithm>

class memorySim
{
    private:
        int algorithm = 1;
        vector<string> data;
        vector<string> memoryBlock;
        vector<string> fileContents;
        int memSize = 0;
        int dataPos = 0;
        int finishTime = 0;
        int startTime = 0;
        


    public:
        memorySim(){} //default constructor
        int lastPos = 0;
        bool hasHitEnd = false;


        //getters

        vector<string> getBlock()
        {
            return memoryBlock;
        }

        vector<string> getData()
        {
            return data;
        }

        vector<string> getFileContents()
        {
            return fileContents;
        }

        int getAlg()
        {
            return algorithm;
        }

        int getMemSize()
        {
            return memSize;
        }

        int getMaxSteps();

        //setters

        void setAlg(string alg)
        {
            if (alg == "first")
                algorithm = 1;
            else if (alg == "next")
                algorithm = 2;
            else if (alg == "best")
                algorithm = 3;
            else
                cout << "ERROR --> '" << alg << "' not recognized as an acceptable algorithm!" << endl;
            
        }

        void setAlg(vector<string> fileContents)
        {
            string algorithmName = "";
            if (fileContents.front() == "first")
            {
                algorithmName = "first";
                setAlg(algorithmName);
            }
            if (fileContents.front() == "best")
            {
                algorithmName = "best";
                setAlg(algorithmName);
            }
            else if (fileContents.front() == "next")
            {
                algorithmName = "next";
                setAlg(algorithmName);
            }
        }

        void setMemSizeFromFile(vector<string> fileContents)
        {
            istringstream iss (fileContents[1]);
            iss >> memSize;
        }

        void setMemSize(int size)
        {
            memSize = size;
        }

        void storeData(vector<string> fileContents, int start);
        void loadBlock(vector<string> content);
        void initVector(int size);
        bool loadFile(string fileName);
        void clearBlock(int timeStep);
        void printBlock();
        bool insertDataFirst(int process_size, int finish_time, int curr_time);
        bool insertDataNext(int processk_size, int finish_time, int curr_time);
        bool insertDataBest(int process_size, int finish_time, int curr_time);
        tuple<int,int,int> selectBest(vector<tuple<int, int, int>> possiblePositions);
        void insertIntoMemory(int start_pos, int finish_pos, int curr_time,int finish_time);
        void AlgFit(int numSteps);
        

        


        
};




#endif