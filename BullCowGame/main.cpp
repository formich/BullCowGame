/* This is the console executable that makes use of the BullCaw class
This acts as the view in the MVC pattern, and is responsible for all
use interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h";
#include "main.h";


using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
bool AskToPlayAgain();

// Instantiate a new game
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
	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries) { 	// TODO change from FOR to WHILE loop once we are validating tries
		FText Guess = GetValidGuess();

		// submit the valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		std::cout << "Your guess was: " << Guess << std::endl;
	}
	//TODO Summarize Game
}

void PrintIntro() {
	// introduce the game
	int32 HiddenWordLength = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << HiddenWordLength << " letter isogram I'm thinking of?" << std::endl << std::endl;
	return;
}


// loop until the user give a valid guess 
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Plese enter a word without repeating letter.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no error
	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again? ";
	std::string Resposne;
	std::getline(std::cin, Resposne);
	return (Resposne[0] == 'y' || Resposne[0] == 'Y');
}