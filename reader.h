#ifndef READER_H
#define READER_H

#include <fstream>
#include "dstring.h"
#include <vector>
using namespace std;
class Reader
{
private:
ifstream tests;
vector<int>Results;         //Results reads if a tweet is a 4 or 0
vector<vector<DString>>Tweet;    //This vector hold a tweet which is parsed into seperate words

public:
   Reader(DString, DString);      //constructor
   void Readtest(DString);       //this reads data file
   void ReadResults(DString);    //this reads target file
   void write(int);              //this writes files for either positive or negative words
   void CreateEndFile(DString);  //this creates the end file for both positive/negative words
    //will these return what we want?
};

#endif // READER_H
