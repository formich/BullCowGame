#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// All values initialized to zero
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

	void Reset(); // TODO make a more rich return value
	
	// Counts bows and cows and increases try #
	FBullCowCount SubmitValidGuess(FString);

// ^^ Please try and ignore this and focus on the interface above ^^
private:
	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
};