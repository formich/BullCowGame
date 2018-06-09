/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/

#pragma once

#include <string>

// to make syntax unreal friendly

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus {
	OK
};

class FBullCowGame {
public:
	FBullCowGame(); // Constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	
	// Counts bows and cows and increases try #
	FBullCowCount SubmitValidGuess(FString);

// ^^ Please try and ignore this and focus on the interface above ^^
private:
	bool IsIsogram(FString) const;
	bool isLowerCase(FString) const;
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
};