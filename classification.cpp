#include "classification.h"
#include <algorithm>
using namespace std;
classification::classification(DString file, DString ScoreFile, DString FileName)
{
        GetScores(ScoreFile);
        RTweets(file,FileName);
}
void classification::GetScores(DString SName) {
    ifstream Reader2;
    Reader2.open(SName.c_str());    //Opening file and error handling
    if (!Reader2) {
        cerr << "Classification File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    while(Reader2.good()) {
        int score;
        Reader2 >> score;
        DString Words;
        Reader2 >> skipws >> Words;  //Scoring file has excess whitespace so will try and bypass it
        DString Word2;
        Word2 =  Words.substring(1,Words.getLength());
        WVect.push_back(Word2);
        Scores.push_back(score);
    }
    Reader2.close();
}
void classification::RTweets(DString FName,DString FileName) {
    DString delimit = " ,./?;:'!@#)`~$%^&*-(_+=|\"";
    vector<int> tes;        //You will see this is similar to the reader class.
    ifstream Reader;
    Reader.open(FName.c_str());
    if (!Reader) {
        cerr << "Classification File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    char buffer[1000];   //we will use this as a getline buffer
    int counter = 0;
    Reader.ignore(256, '\n');
    while(Reader.getline(buffer, 999, '\n')) {
        int Talley = 0;
        char* tokenBuffer;  //This is our second buffer to seperate words
        tokenBuffer = strtok(buffer, ",");
        int push = atoi(tokenBuffer);
        Nums.push_back(push);
        tokenBuffer = strtok(NULL, ",");   //Continue to use this buffer until the line ends
        long IPush = atol(tokenBuffer);
        IDs.push_back(IPush);               //Storing the ID for printing later on
        tokenBuffer = strtok(NULL, delimit.c_str());
        while(tokenBuffer != NULL) {
            DString Tweet{tokenBuffer};      //We are seperating each word from a tweet and checking if it exists in Scores
            auto iter= lower_bound(WVect.begin(),WVect.end(),Tweet);
            int index = -(WVect.begin() - iter);
            Talley += Scores[index];
            tokenBuffer = strtok(NULL, delimit.c_str());   //loop buffer until the line ends
        }
        Tallies.push_back(Talley);    //We add it to a vector of Tallies for output later in the file
                counter++;
    }
    Reader.close();
    OutputTotal(FileName);
}
//in this method we will be creating our final file
void classification::OutputTotal(DString FileName) {
    int i = 0;
    for (auto & loop: Tallies) {
        if (Tallies[i] > 0) {
            int pos = 4;
            GoodOrBad.push_back(pos);
            }//This means the tweet was good, since it had a positive score
        else {
            int neg = 0;
            GoodOrBad.push_back(neg);
            }//since this pushes 0, that means the tweet had a score of 0 or lower
        i++;
    }
    ofstream file;
    file.open(FileName.c_str());
    if (file.is_open())
    {               //Now we write this all to a file that was inputted in the command line
        int count = 0;
        for (auto & g: GoodOrBad) {
            file << IDs[count] << " ";
            file << GoodOrBad[count]  << endl;
            count++;
        }
    }
    file.close();
}
