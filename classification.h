#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H
#include "dstring.h"
#include "dvector.h"
#include <fstream>
class classification
{
private:
    /**
     * These vectors are holders for various variables
     *  i.e. Tallies hold the total scores for each individual tweet
     * Scores is the map i use to hold a word and its value in respect to my scoring algorithim
     * GoodOrBad holds total result of  tweets which I will index later
     **/
    DVector<int>Tallies;
    DVector<DString>WVect;
    DVector<int>Scores;
    DVector<int>GoodOrBad;
    DVector<int> Nums;
    DVector<long> IDs;
public:
    classification(DString, DString, DString);
    void RTweets(DString,DString);
    void GetScores(DString);
    void OutputTotal(DString);
};

#endif
