/* This is the console executable that makes use of the BullCaw class
This acts as the view in the MVC pattern, and is responsible for all
use interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h";
#include "main.h";

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGammeSummary();

// Instantiate a new game globally accessible
FBullCowGame BCGame;


// the entry point for our application
int main() {
	PrintIntro();
	do {
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for the number of turns asking for guesses
	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit the valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		std::cout << "Your guess was: " << Guess << std::endl;
	}
	PrintGammeSummary();
	return;
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


// loop until the user give a valid guess 
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Plese enter a word without repeating letter.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
			return Guess;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no error
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? (y/n)";
	std::string Resposne;
	std::getline(std::cin, Resposne);
	return (Resposne[0] == 'y' || Resposne[0] == 'Y');
}

void PrintGammeSummary() {
	if (BCGame.isGameWon())
		std::cout << "YOU WIN!\n\n";
	else
		std::cout << "Better luck next time!\n\n";
}
