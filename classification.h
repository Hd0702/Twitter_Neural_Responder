#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H
#include "dstring.h"
#include <vector>
#include <fstream>
#include <map>
class classification
{
private:
    /**
     * These vectors are holders for various variables
     *  i.e. Tallies hold the total scores for each individual tweet
     * Scores is the map i use to hold a word and its value in respect to my scoring algorithim
     * GoodOrBad holds total result of  tweets which I will index later
     **/
    std::vector<int>Tallies;
    std::map<DString,int>Scores;
    std::vector<int>GoodOrBad;
    std::vector<int> Nums;  //These two hold values from Data-train file for printing final file
    std::vector<long> IDs;  
public:
    classification(DString, DString, DString);   //Constructor
    void RTweets(DString,DString);              //These reads whole testing file
    void GetScores(DString);                    //This reads the scoring file and stores it
    void OutputTotal(DString);                  //This method executes after above methods to get final score
};

#endif
