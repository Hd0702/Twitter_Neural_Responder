#ifndef READER_H
#define READER_H

#include <fstream>
#include "dstring.h"
#include <vector>
#include "dvector.h"
using namespace std;
class Reader
{
private:
ifstream tests;
DVector<int>Results;
DVector<DVector<DString>>Tweet;    //This vector hold a tweet which is parsed into seperate words

public:
   Reader(DString, DString);
   void Readtest(DString);
   void ReadResults(DString);
   void write(int);
   void CreateEndFile(DString);
};

#endif // READER_H
