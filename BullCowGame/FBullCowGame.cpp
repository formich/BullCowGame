#pragma once

#include "FBullCowGame.h"
#include <map>

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString  HIDDEN_WORD = "planet"; //this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	std::map<int32, int32> WordLengthToMaxTries{ {3,4} , {4,7} , {5,10}, {6,16} , {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 	// if the guess is not an isogram
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!isLowerCase(Guess)) // if the guss is not all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // if the guess' length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}


//Receives a VALID guess, increments turn and returns count 
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	int32 GuessWordLength = Guess.length();

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < GuessWordLength; GChar++) {
			// if the letters match
			if (Guess[GChar] == MyHiddenWord[MHWChar])
				// in the same place increment bulls
				if (MHWChar == GChar)
					BullCowCount.Bulls++;
				// otherwise inrement cows
				else
					BullCowCount.Cows++;
		}
	}
	if (BullCowCount.Bulls == WordLength)
		bGameIsWon = true;
	else
		bGameIsWon = false;
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter word as isogram
	if (Word.length() <= 1)
		return true;

	std::map<char, bool> LetterSeen;

	for (char Letter : Word) {
		Letter = tolower(Letter); // handle mix case
		if (LetterSeen[Letter])
			return false; // we don't have an isogram
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true; // for example in ase wehre /0 is entered
}

bool FBullCowGame::isLowerCase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter))
			return false;
	}
	return true;
}
