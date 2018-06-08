#include "FBullCowGame.h"
#include <map>
#define TMap std::map;

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString  HIDDEN_WORD = "planet";
	MyMaxTries = MAX_TRIES;
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
	return MyMaxTries;
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
	else if (false) // if the guss is not all lowercase
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
	// loop through all the letter of the word
		// if the letter is in the map
			// we don't have an isogram
		// otherwise
			// add the letter to the map as seen
	return true; // for example in ase wehre /0 is entered
}
