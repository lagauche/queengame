/*
This is the console executable, that makes use of the FQueenGame class. 
This acts as the view in a MVC pattern, and is responsible for all user interaction. 
For game logic see the FBullCowGame class
*/
#pragma once
#include <iostream>
#include <string>
#include "FQueenGame.h"

// to make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText Guess = "";
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FQueenGame QGame; // instantiate a new game, which we re-use across plays

// entry point for our application
int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	
    return 0; // exit the application
}

void PrintIntro() {
	std::cout << "Hey Queens! Can you guess the " << QGame.GetHiddenWorthLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << R"(
                                                                          ;"  `;
     _                                                                    |`--'|
    ( `,                                                                  |    |
    |`._)                                          _____________          |    |
    |   |                             __          |+-----------+|         |    |
    |   |                           /`  `\        ||           ||         |    |
    |___|                          |      |       ||           ||         |    |
   (_____)                         |      |       ||           ||         |    |
   |     |                         |      |       |L-----------j|         |    |
   |     |     _____________      / `.__.` \     / +----+---+  /          |    |
   |     |   ,`          ,` `,   |          |   / /    /   /  /           '.__.`               _______________
   |_____|   "           '   '    \        /   / +----+----+ /                ,,,,,,,_________/\              \
  (_______)  ".__________',_,'     \______/   (_____________/                 ;;;;;;;----------/______________/
                                                    ,--------,'".
                                                    `--------`.."          
)" << '\n';
	return;
}

// plays a single game to completion
void PlayGame() 
{
	QGame.Reset();
	int32 MaxTries = QGame.GetMaxTries();
	std::cout << "You have " << MaxTries << " guesses" << "\n\n";

	// loop asking for a guess while the game is NOT won and there are tries remaining
	while(!QGame.IsGameWon() && QGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FQueerStr8Count QueerStr8Count = QGame.SubmitValidGuess(Guess);
		
		std::cout << "Queers = " << QueerStr8Count.Queers;
		std::cout << ". Str8s = " << QueerStr8Count.Str8s << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get guess from the player
		int32 CurrentTry = QGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << QGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = QGame.CheckGuessValidity(Guess);
		switch (Status) // switch based on some expression
		{
		case EGuessStatus::Wrong_Length: // in the case of some constant...
			std::cout << "Please enter a " << QGame.GetHiddenWorthLength() << " letter word.\n\n";
			break; // come out of the switch statement
		case EGuessStatus::Not_Isogram:
			std::cout << "You gotta enter a word without repeating letters\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Ah! The game only understands lowercase words!\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "play again with the same word (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (QGame.IsGameWon())
	{
		std::cout << "Congrats! All the queers are in their right place! \n\n";
	}
	else
	{
		std::cout << "The st8s dominated, but you'll get um next time!\n\n";
	}
}


