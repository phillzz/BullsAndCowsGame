#pragma once
// Unreal Engine standarts
using FString = std::string;
using int32 = int;
// Container for Bulls and Cows count.
struct SBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};
// Validator enumeration of all statuses
enum class EValidityStatus
{
	Invalid_Status,
	IncorrectLenght,	
	NotIsogram,	
	ContainNonAlphabetCharacter,
	Repeating,
	OK
};
// Game class declaration 
class FBullCowGame
{
public:
	FBullCowGame();

	void Reset();
	
	//TODO: REFACTOR MaxTries auto calculation method
	int32 GetMaxTries();
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght();
	FString GetHiddenWord();
	FString CaseCorrection(FString);

	bool IsGameWon() const;

	EValidityStatus CheckGuessValidity(FString);
	SBullCowCount SetGuess(FString);
// Local variables
private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString OriginWord;
	bool bIsGameWon;

	bool bIsRepeat(FString) const; 
	bool bIsIsogram(FString) const;
	bool bIsAlphabet(FString) const;

};


//TODO: Add best score method.
//TODO: Add achivement method.