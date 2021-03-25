//Ulysis Llanes
// cs 301
// evil hang man
// 12/2/19
// Erickson

#include <string>
#include <iostream>
#include <stdlib.h>
#include "FamilySet.h"

using namespace std;

bool debug;	// Global variable to indicate debugging

bool PromptYesNoMessage( string msg ) {     // you did this

	while ( true ) {

		cout << msg << "(y/n) ";
		string response;
		cin >> response;

		if ( response == "y" )
			return true;

		if ( response == "n" )
			return false;

		cout << "Please enter y or n..." << endl;

	}

}

int PromptGuesses()
{

	while ( true ) {

		int len;

		cout << "Please enter how many guesses: ";      // get number of guesses
		cin >> len;

		if ( len > 0 )                          // cant be less than 0
			return len;

	}

}

int PromptWordLength()
{

	int len = 30;       // intiates the while loop

    while( len >= 30 || ( len == 27  || len == 26 ) || len < 1 || len == 25 ){  // doesnt have words associated with the length

	cout << "Enter number of letters you want in a word: ";
	cin >> len;

    }

	return len;

}

string PromptGuess( string& guessedLetters )
{
	string guess = "";
	bool breakB = true;

	while( true ){

        cout << "Enter a letter to guess the word: ";
        cin >> guess;

        if( guessedLetters.size() == 0 )                    // the start break loop
            break;


        for( int m = 0; m < guessedLetters.length(); m++ ){

            if( guess[ 0 ] == guessedLetters[ m ] ){            // if the word already guessed

                cout <<"You have already entered this letter, enter another letter!! "<< endl;
                breakB = true;

            }
            else{

                breakB = false;             // if the letter doesnt exist

            }

        }

        if ( breakB == false ) {

            break;
        }

	}

	guessedLetters = guessedLetters + guess; // add guess to already guessed letters

	return guess;

}

string ChooseFamily( string guess, string guessProgress, FamilySet& set )
{
	// filter families by guess and guessProgress
    set.filterFamilies( guess, guessProgress );     // make families for the guess and guess progress

	string maxFamily;
    maxFamily = set.getNextFamily();        // get the family with most word
	return maxFamily;                   // return family with most words

}

bool isWin( string guessedProgress )
{
	return guessedProgress.find( "*" ) == string::npos;
}

void PlayEvilHangman( string file )
{

    int len = PromptWordLength();           // number of letters in word
    int guessesLeft = PromptGuesses();  //number of guesses

	cout << "Loading dictionary..." << endl << endl;

	FamilySet families( file, len );

    string guessProgress;
	string guessedLetters = "";
	string correctlyGuessed = "";	// correctly guessed positions
	string guess;

	for ( int i = 0; i < len; i++ )
            guessProgress += "*";           // make it visual for user to see the letters  not found


	// Actual game loop...
	while ( true ) {

        cout << "The Word now: " << guessProgress << endl;
        cout << "Number of guesses left: " << guessesLeft << endl;
        cout << "Guessed letters:" << guessedLetters << endl;

        if( PromptYesNoMessage( "Reveal the number of words left? " ) ){

            cout << "Number of words left: " << families.numWords() << endl;       // print number of words found remaining

        }


                                               // user guesses letter
        guessProgress = ChooseFamily( PromptGuess( guessedLetters ), guessProgress, families );                 // gets the new guess prgress
        families.setFamily( guessProgress );
        guessesLeft-=1;                                              // decrement guesses left



		if ( isWin( guessProgress ) ) {

			cout << "Wow! You won!" << endl;
			cout << "The word is " << guessProgress << endl;        //reveal word
			break;

		}

		if ( guessesLeft <= 0 ) {

			cout << "Wow... you are a really bad guesser..." << endl;
			cout << "The mystery word was " << families.getRandomWord() << endl;    // get random word from list left
			break;

		}

	}

}

int main()
{
	string file;
	file = "dictionary.txt";

	while ( true ) {

		debug = PromptYesNoMessage( "Turn debugging on?" );
		PlayEvilHangman( file );

		if ( !PromptYesNoMessage( "Would you like to play again ?" ) )
            break;

        system( "CLS" );                            // clear screen for neatness

	}

	return 0;

}

