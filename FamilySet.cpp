#include "FamilySet.h"
#include <string>

// DONE
FamilySet::FamilySet()
{
    ifstream myFile;
    myFile.open("dictionary.txt");                  // opened the dictionary file
    string word;


    while(myFile){                                  // while the myFile exists
        myFile >> word;                             // store word to myFile
        masterList.push_back(word);                 // add word to the back of the array
        iterCount++;

        myFile.eof();                               // reached the end of the file
    }

    myFile.close();                                 // close file
}

FamilySet::FamilySet(string file)
{
    ifstream myFile(file);

    string word;

    while(myFile){

        myFile >> word;
        masterList.push_back(word);
        iterCount++;

        myFile.eof();
    }

    myFile.close();
}

FamilySet::FamilySet(string file, int len)
{
    ifstream myFile(file);

    string word;

    if (!myFile){
        cout << " ** The file did not open! **" << endl;
        exit(0);
    }

    while(myFile){

        myFile >> word;

        long int wordSize = word.size();

        if(wordSize == len){

            masterList.push_back(word);
            iterCount++;

            myFile.eof();
        }
    }

    myFile.close();
}

FamilySet::~FamilySet()
{
    // Optional for this assignment
}

void FamilySet::filterFamilies(string letter, string guessPattern)
{
    dictionaries.clear();




    for( auto it = masterList.begin(); it != masterList.end(); ++it ){

        string MasterWord = *it;
        string NewPattern = guessPattern;
        vector<string> NewVector;

        int f = 0;

        while(f < NewPattern.length()){

            if(MasterWord[f] == letter[0]){
                NewPattern[f] = letter[0];
            }

            f++;
        }


        if(dictionaries.find(NewPattern) != dictionaries.end()){


            dictionaries[NewPattern].push_back(MasterWord);
        }
        else{

           dictionaries[NewPattern] = NewVector;
            dictionaries[NewPattern].push_back(MasterWord);
        }


    }
    // The first step is to clear dictionaries to prepare
    // for the new filter based on the letter and pattern
    // For each word in the master list, you need to classifystring FamilySet::getNextFamily()

    // what family is part of based on the letter and pattern.
    // If you can find letter in the word, then we need to
    // create the new family.
    // Otherwise, if the letter does not exist in the word, then
    // the family is simply the guessPattern.
    // Example 1:Suppose letter is "a", word is "ally", and
    //           guessPattern is ***y.
    //           In this case, the family is a**y. Once this
    //           is determined, then "ally" can be added to
    //           the "a**y" dictionary.
    // Example 2:Suppose letter is "a", word is "cool", and
    //           guessPattern is ***y.
    //           In this case, the family is ***y and "cool"
    //           would be added to the ***y dictionary.
}

void FamilySet::setFamily(string family)
{
    resetFamilyIter();
    masterList = getFamily(family);
    iterCount = familySize(family);

    // This updates the master list.  The new master list
    // should contain the words within the dictionary for family.
    // dictionaries should be cleared after updating the master list.

}

vector<string> FamilySet::getFamily(string family)
{
    vector<string> TheDictionary = dictionaries[family];
    return dictionaries[family];
}


string FamilySet::getRandomWord()
{
    string RandWord = masterList[rand()%iterCount];
    return RandWord;
}


int FamilySet::numWords()
{
    // This should return the number of words in the master list
    return iterCount;
}

int FamilySet::numFamilies()
{


    int famNum = 0;
    for(auto it = dictionaries.begin(); it!= dictionaries.end(); ++it){

        famNum ++;

    }

    return famNum;
}

void FamilySet::resetFamilyIter()
{
   masterList.clear();
   iterCount = 0;
}



string FamilySet::getNextFamily()
{
    int TopFamily = 0;
    string TopFamString;

    for ( pair<string, vector <string>> elem :dictionaries){

        if(familySize(elem.first)> TopFamily){

            TopFamily = familySize(elem.first);
            TopFamString = elem.first;

        }

    }

    return TopFamString;
}


int FamilySet::familySize(string family)
{
    // Returns the size of the dictionary of family
    int FamSize = dictionaries[family].size();

    return FamSize;
}



