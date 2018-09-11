#include "reader.h"
#include <iterator>
#include <list>
#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
Reader::Reader(DString file1name, DString file2name)
{
    Readtest(file1name);   //We are reading the data file first
    ReadResults(file2name);  //then we read the target file
}

void Reader::Readtest(DString fname) {
    DString delimit = " ,./?;:'!@#)`~$%^&*-(_+=|\"";   //This will be our delimiter for str_tok
    tests.open(fname.c_str());                          //holding only utf-8 characters gives a more accurate algorithim
    if (!tests) {
       cerr << "File1 can not open" << endl;        //error handling
       exit(EXIT_FAILURE);
    }
    tests.ignore(256, '\n');
    char r [1000];    //this char will be our buffer
    while (tests.getline(r,999, '\n')) {  //read each line into the buffer
        DString comma = ",";
        vector<DString>SinTweet;
        char *token;            //this token is our buffer for spliting file
        token= strtok(r,",");    //read first number into a token
        DString num{token};
        token = strtok(NULL, ",");   //no need to store num so we wont add it to a vector
        DString ID{token};           //Same goes with ID
        token = strtok(NULL, delimit.c_str());
        while (token != NULL) {
            DString temp{token};        //This loop breaks a whole line into individual tweets...
            SinTweet.push_back(temp);   //which we will then add to a vector
            token = strtok(NULL, delimit.c_str());
        }
        Tweet.push_back(SinTweet); //we add our vector to our 2D vector
    }
    tests.close();
}

void Reader::ReadResults(DString fread) {    //This function reads the target file
    tests.open(fread.c_str());
    if (!tests) {
        cerr << "results could not be read" << endl;
        exit(EXIT_FAILURE);
    }
    char reader [500];      //reader will be our buffer
    while(tests.getline(reader, 499, '\n')) {
        int Num;
        tests >> Num;
        tests.ignore(1, ',');  //CSV files have commas so we must ignore them
        int Result;
        tests >> Result;        //Result tells us if the tweet has a 0 or 4
        tests.ignore(1, ',');       //it is THE most important part of this function
        long ID;
        tests >> ID;
        Results.push_back(Result);    //we add it to a vector that holds all Results
    }
    tests.close();
}
void Reader::write(int pon) {   //We will call this function twice in main
    long index{0};              //if pon = 0 we will be creating positive word file
    long i3{0};                 //if pon = 4 we will create negative word file
    vector<int> c;
    vector <DString> posword;
    for (auto & c : Tweet) {      //We are going to iterate over each full tweet
        if (Results[index]== pon) {   //If that tweet has a 0 OR 4 (whatever pon is) we will add that file to a vector...
            for (auto & d : c) {            //which we will then use in file creation
               DString b = Tweet[index][i3];
               DString a = b.c_str();     //We want to be safe and make sure we have no ambiguous values with a word in Tweet
               posword.push_back(a);
               i3++;   //i3 loops through Each individual word
            }
            i3=0;
        }
      index ++;   //index loops through each tweet
    }
    index = 0;
    sort(posword.begin(), posword.end());   //Now we will use overloaded < operator to sort our vector of good/bad words
    vector<DString> p = posword;
    map<DString,int> maps;    //This map will be important later because it indexs MUCH faster than a vector
    p.erase(unique(p.begin(),p.end()), p.end());    //now we will have vector that stores ONE instance of each good/bad word
    int loop{0};
    for (auto & f : p){
        maps.insert(make_pair(p[loop],0));   //This adds a key for each indivdual good/bad word and sets the value to 0
        loop++;
    }
    loop=0;
    for (auto & b :posword) {      //Now we count freq. of a certain bad/good word by looping through complete word vector
        maps[posword[loop]]++;   //if Word exists in maps we increase value by 1
        loop++;
    }
    ofstream fileWrite;  //This will create either or good or bad file
    if (pon == 0)
        fileWrite.open("Negative_Words.txt");
    else if (pon == 4)
        fileWrite.open("Positive_Words.txt");
    for (auto & loops: maps) {      //We want bad values to be negative for calc. later
        if (pon == 0)
            fileWrite << -(loops.second) << " " << loops.first << endl;
        if (pon == 4) {
            fileWrite << loops.second << " " << loops.first << endl;
        }
    }
    fileWrite.close();
}
void Reader::CreateEndFile(DString FileName) { // this method creates our final file for scoring algorithim
    ifstream neg;
    ifstream pos;
    neg.open("Negative_Words.txt");  //We want to open BOTH files and store them
    pos.open("Positive_Words.txt");
    vector<int>NegScores;
    vector<DString>NegWords;
    vector<int>PosScores;
    vector<DString>PosWords;
    vector<DString>FinalWord;
    vector<double>FinalScore;
    if(!neg) {
        cerr << "Negative_Words.txt could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    if(!pos) {
        cerr << "Positive_Words.txt could not be opened" << endl;
        exit(EXIT_FAILURE);
    }
    while(neg.good()) {
        int score;     //This stores individual negative values/words
        neg >> score;
        DString Read;
        neg >> Read;
        NegScores.push_back(score);
        NegWords.push_back(Read);

    }
    neg.close();
    while(pos.good()) {   //this stores individual good values/words
        int score;
        pos >> score;
        DString File;
        pos >> File;
        PosScores.push_back(score);
        PosWords.push_back(File);
    }
    pos.close();
    int counter{0};
    for (auto & a: PosWords) { //Now we will iterate through every word and assign it a final score
        auto iter = lower_bound (NegWords.begin(), NegWords.end(), PosWords[counter]); //This searches if a word Exists in Both by a speed of log(n)
        if ( iter != NegWords.end() && *iter == PosWords[counter]) {  //if the word is found
            int index = distance(NegWords.begin(), iter);
            if (PosScores[counter] == 0) {  //this is if index is 0 we will have a special case to avoid divide/0
                PosScores[counter] = 1;
            }
            if (-(NegScores[index]) > PosScores[counter]) {  //if negative number is higher we will associate score to neg number
                int store = -NegScores[index]/PosScores[counter];
                store = -store;
                FinalScore.push_back(store);
                FinalWord.push_back(PosWords[counter]);

            }
            else if (PosScores[counter] > -NegScores[index]) {  //if positive occurances are higher we associate score as positive for certain word
                int store = PosScores[counter]/-NegScores[index];
                FinalScore.push_back(store);
                FinalWord.push_back(PosWords[counter]);
            }
            else {  //if occurances are the same amount in both negative and positive tweets
                int store = PosScores[counter];
                FinalScore.push_back(store);
                FinalWord.push_back(PosWords[counter]);

            }
            counter++;
        }
        else {  //if the word isnt found add in the negative word vector, associate as positive
            FinalScore.push_back(PosScores[counter]);
            FinalWord.push_back(PosWords[counter]);
            counter++;
        } // what about the rest of the negative words?? well we have to do those too
    }
    counter = 0;
    for ( auto & b : NegWords) {  //This seaches for negative words and positive words just like above
        auto iter = lower_bound (PosWords.begin(),PosWords.end(), NegWords[counter]);
              if (iter == PosWords.end()) {       //NOW we add the word to negative because we dont have only negative occurances added yet
                  int store = NegScores[counter];
                  FinalScore.push_back(store);
                  FinalWord.push_back(NegWords[counter]);
              }
              counter++;
    }
    ofstream final;
    final.open(FileName.c_str());   //Now we write to algorithim file which we will use in output
    int count = 0;
    for (auto & i: FinalWord){
        final << FinalScore[count] << FinalWord[count] << endl;
        count ++;
    }
    final.close();
}
