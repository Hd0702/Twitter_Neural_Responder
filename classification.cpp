#include "classification.h"
#include <algorithm>
#include <string>
using namespace std;
classification::classification(DString file, DString ScoreFile, DString FileName)
{
        GetScores(ScoreFile);    //We want to read scoring file first to store in Scores map
        RTweets(file,FileName);  //We then use our variables from GetScores to make reading RTweets easier
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
        Reader2 >> skipws >> Words;  //Scoring file had excess whitespace so  we try and bypass it
        DString Word2;              //The next two lines are ensuring we dont have any whitespace preceeding a string
        Word2 =  Words.substring(1,Words.getLength());
        Scores.insert(make_pair(Word2,score));  //We are storing these values in a map because they are fast containers
    }                                           // Much faster to search than vectors
    Reader2.close();
}
void classification::RTweets(DString FName,DString FileName) {
    DString delimit = " ,./?;:'!@#)`~$%^&*-(_+=|\"";
    vector<int> tes;        //You will see this is similar to the reader class.
    ifstream Reader;        //We are essentially doing something similar, but ALSO adding scores to a tweet using Talley
    Reader.open(FName.c_str());
    if (!Reader) {                                   //Error Handling
        cerr << "Classification File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    char buffer[1000];   //we will use this as a getline buffer
    int counter = 0;
    Reader.ignore(256, '\n');
    while(Reader.getline(buffer, 999, '\n')) {
        int Talley = 0;
        char* tokenBuffer;  //This is our second buffer to seperate words
        tokenBuffer = strtok(buffer, ",");   //Reading Tweet number and storing it
        int push = atoi(tokenBuffer);
        Nums.push_back(push);
        tokenBuffer = strtok(NULL, ",");   //Continue to use this buffer until the line ends
        long IPush = atol(tokenBuffer);
        IDs.push_back(IPush);               //Storing the ID for printing later on
        tokenBuffer = strtok(NULL, delimit.c_str());
        while(tokenBuffer != NULL) {         //This is where we handle the strings
            DString Tweet{tokenBuffer};      //We are seperating each word from a tweet and checking if it exists in Scores map
            if (Scores.count(Tweet) == 1) {   //If it DOES exist in the map, then we add the score from the Scores.second
                Talley += Scores[Tweet];
            }
            tokenBuffer = strtok(NULL, delimit.c_str());   //loop buffer until the line ends
        }
        Tallies.push_back(Talley);    //We add it to a vector of Tallies for output later in the file
                counter++;
    }
    Reader.close();
    OutputTotal(FileName);
}
void classification::OutputTotal(DString FileName) {  //in this method we will be creating our final file
    int i = 0;                      //We will loop through tallies and if its positive we will index a tweet as good/bad
    for (auto & loop: Tallies) {
        if (Tallies[i] > 0)
            GoodOrBad.push_back(4);     //This means the tweet was good, since it had a positive score
        else
            GoodOrBad.push_back(0);    //since this pushes 0, that means the tweet had a score of 0 or lower
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
