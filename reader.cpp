#include "reader.h"
#include <iterator>
#include <list>
#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
Reader::Reader(DString file1name, DString file2name)
{
    Readtest(file1name);
    ReadResults(file2name);
}

void Reader::Readtest(DString fname) {
    DString delimit = " ,./?;:'!@#)`~$%^&*-(_+=|\"";   //This will be our delimiter for str_tok
    tests.open(fname.c_str());
    if (!tests) {
       cerr << "File1 can not open" << endl;
       exit(EXIT_FAILURE);
    }
    tests.ignore(256, '\n');
    char r [1000];
    while (tests.getline(r,999, '\n')) {  //read each line into the buffer
        DString comma = ",";
        DVector<DString>SinTweet;
        char *token;            //this token is our buffer for spliting file
        token= strtok(r,",");
        DString num{token};
        token = strtok(NULL, ",");   //no need to store num so we wont add it to a vector
        DString ID{token};
        token = strtok(NULL, delimit.c_str());
        while (token != NULL) {
            DString temp{token};        //This loop breaks a whole line into individual tweets...
            SinTweet.push_back(temp);
            token = strtok(NULL, delimit.c_str());
        }
        Tweet.push_back(SinTweet);
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
        tests.ignore(1, ',');
        long ID;
        tests >> ID;
        Results.push_back(Result);    //we add it to a vector that holds all Results
    }
    tests.close();
}
//We will call this function twice in main
void Reader::write(int pon) {
    long index{0};              //if pon = 0,4 creates negtive,positive file respectively
    long i3{0};
    DVector<int> c;
    DVector <DString> posword;
    for (auto & c : Tweet) {      //We are going to iterate over each full tweet and add each word to a vector
        if (Results[index]== pon) {
            for (auto & d : c) {
               DString b = Tweet[index][i3];
               DString a = b.c_str();
               posword.push_back(a);
               i3++;   //i3 loops through Each individual word
            }
            i3=0;
        }
      index ++;   //index loops through each tweet
    }
    index = 0;
    sort(posword.begin(), posword.end());
    DVector<DString> pas = posword;
    DVector<pair<DString,int>> Pairs;       //Pairs holds both a word and how frequently it appears
    auto uniq = unique(pas.begin(),pas.end());
    int change =  uniq-pas.begin();   //this will return location of where duplicates appear
    DVector<DString> p;
    int d = 0;
    for (auto iter = pas.begin(); d < change; iter++){
        p.push_back(*iter);    //we are putting only unique elements into p
        d++;
    }
    for (auto ite = p.begin(); ite != (p.end()); ite++){
        pair<DString,int> maps;
        DString place = *ite;
        maps.first = place;              //we are setting each value into a temporary pair
        maps.second = 1;
        Pairs.push_back(maps);   //we now add the pair to our vector of pairs
    }
    int stored= 0;
    for (auto it = Pairs.begin(); it != Pairs.end(); it++) {   //this iterates through pairs and adds frequency of each key
         for(int i = stored ; i< posword.getsize(); i++) {
             if(it->first == posword[i]) {         //since posword is sorted they should all appear in order
                 (it->second)++;
                 stored++;
             }                              //since stored is our loop variable we have to add to it as a refrence point
             else {
                 stored++;
                 break;                     //once we reach the end of a sorted word we will break to save runtime
             }
         }
    }
    //This will create either or good or bad file
    ofstream fileWrite;
    if (pon == 0)
        fileWrite.open("Negative_Words.txt");
    else if (pon == 4)
        fileWrite.open("Positive_Words.txt");
    for (auto ite = Pairs.begin(); ite != Pairs.end(); ite++) {
        if (pon == 0)
            fileWrite << -(ite->second) << " " << ite->first << endl;
        if (pon == 4) {
            fileWrite << ite->second << " " << ite->first << endl;
        }
    }
    fileWrite.close();
}
// this method creates our final file for scoring algorithim
void Reader::CreateEndFile(DString FileName) {
    ifstream neg;
    ifstream pos;
    neg.open("Negative_Words.txt");  //We want to open BOTH files and store them
    pos.open("Positive_Words.txt");
    DVector<int>NegScores;
    DVector<DString>NegWords;
    DVector<int>PosScores;
    DVector<DString>PosWords;
    DVector<DString>FinalWord;
    DVector<int>FinalScore;
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
    for (int i =0; i < PosWords.getsize(); i++) { //Now we will iterate through every word and assign it a final score
        auto iter = lower_bound (NegWords.begin(), NegWords.end(), PosWords[counter]);
       if ( iter != NegWords.end() && *iter == PosWords[counter]) {  //if the word is found

            auto index = (iter - NegWords.begin());
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
    for (int i =0; i < NegWords.getsize(); i++) {  //This seaches for negative words and positive words just like above
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
    for (int i =0; i <FinalWord.getsize(); i++){
        final << FinalScore[count] << FinalWord[count] << endl;
        count ++;
    }
    final.close();
}
