//Programmer: Skylar Trendley
//Class: CS3800 (Operating Systems)
//Professor: Dr. Wilkerson
//Description: Safe Multithreading

#include <iostream>
#include <queue>
#include <mutex>
#include <fstream>
#include <vector>
#include <thread>
#include <functional>
using namespace std;

const string dataFolder = "data/data/";
mutex mutFileQueue;
mutex mutWordQueue;

void loadQueue(queue<string>& fileQueue)
{
    ifstream inStream;
    string bookContents;
    
    inStream.open(dataFolder + "files.dat");
    if(!inStream)
    {
        cout << "ERROR HAS OCCURRED: FILE COULD NOT BE OPENED" << endl;
        return;
    }

    else
    {
        while(inStream >> bookContents)
        {
            fileQueue.push(bookContents);
        }
    }

    inStream.close();

}


void mapperThread(queue<string>& fileQueue, queue<int>& wordQueue, string keyWord)
{
    string top;
    int numWords = 0;    
    
    ifstream inStream;
    string bookContents;

    //lock the file queue, remove top file name, & unlock file queue
    mutFileQueue.lock();
    top = fileQueue.front();
    fileQueue.pop();
    mutFileQueue.unlock();

    //open the file, count instance of words, then close file
    inStream.open(dataFolder + top);
    if(!inStream)
    {
        cout << "ERROR HAS OCCURRED: FILE COULD NOT BE OPENED" << endl;
        return;
    }

    else
    {
        while(inStream >> bookContents)
        {
            if(bookContents == keyWord)
                numWords = numWords + 1;
        }
    }

    inStream.close();

    //lock the count queue, push the count, and unlock count queue
    mutWordQueue.lock();
    wordQueue.push(numWords);
    mutWordQueue.unlock();

}

void reducerThread(queue<int>& wordQueue, int index)
{
    int countOne = 0, countTwo = 0, sum = 0;

    while(wordQueue.size() > 1)
    {
        //lock the count queue
        mutWordQueue.lock();

        //remove the top two elements
        countOne = wordQueue.front();
        wordQueue.pop();
        countTwo = wordQueue.front();
        wordQueue.pop();

        //unlock the count queue
        mutWordQueue.unlock();

        //sum the two elements together
        sum = countOne + countTwo;

        //lock the count queue, push the sum onto the queue, and unlock the count queue
        mutWordQueue.lock();
        wordQueue.push(sum);
        mutWordQueue.unlock();

    }
}

int main()
{
    string word;

    vector<thread> mapVec;
    vector<thread> reduceVec;

    //set up the queues
    queue<string> fileQueue;
    queue<int> wordQueue;

    //prompt the user for the word they wish to count
    cout << "Enter the word of which you would like to count: ";
    cin >> word;

    loadQueue(fileQueue);

    for(unsigned int i = 0; i<fileQueue.size(); i++)
    {
        mapVec.push_back(thread(mapperThread, ref(fileQueue), ref(wordQueue), word));
    }

     //launch mapper threads and wait for them to complete the mapping
    for(auto& mapperThread : mapVec)
        mapperThread.join();

    for(unsigned int i = 0; i<wordQueue.size(); i++)
    {
        reduceVec.push_back(thread(reducerThread, ref(wordQueue), i));
    }
    
    //launch reducer thread(s) and wait for them to complete their work
    for(auto& reducerThread : reduceVec)
        reducerThread.join();

    //print out the total count
    if(wordQueue.front() == 0)
    {
        cout << "Error occurred: " << "\"" << word << "\"" <<  " does not exist. Check your spelling." << endl;
    }
    else
    {
        cout << "\"" << word << "\"" << " appeared " << wordQueue.front() << " times." << endl; 
    }
    return 0;
}