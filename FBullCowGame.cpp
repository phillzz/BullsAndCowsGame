#pragma once

#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// Initialize a game default settings
FBullCowGame::FBullCowGame() { Reset(); }
//Getters
int32 FBullCowGame::GetMaxTries() 
{
	TMap <int32, int32> CurrentLenght;

	CurrentLenght[2] = 1;
	CurrentLenght[3] = 2;
	CurrentLenght[4] = 3;
	CurrentLenght[5] = 4;
	CurrentLenght[6] = 5;
	CurrentLenght[7] = 6;

	return CurrentLenght[GetHiddenWordLenght()];

}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght()
{
	FString TEXT = GetHiddenWord();
	return TEXT.length();
}
FString FBullCowGame::GetHiddenWord()
{ 
	const FString HiddenWord = "working";
	OriginWord = HiddenWord;
	return HiddenWord;
}
//Set guess and check for Bulls and Cows count
SBullCowCount FBullCowGame::SetGuess(FString Guess)
{
	MyCurrentTry++;
	SBullCowCount BullCowCount;

	for (int32 i = 0; i < Guess.length(); ++i)
	{
		for (int32 j = 0; j < OriginWord.length(); ++j)
		{
			if ((Guess[j] == OriginWord[i]) && (i == j)) { BullCowCount.Bulls++; }
			else if ((Guess[j] == OriginWord[i]) && (i != j)) { BullCowCount.Cows++; }
		}
	}
	if (BullCowCount.Bulls == GetHiddenWordLenght())
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}
	return BullCowCount;
}
//Validator's container. Check answer for game rules requirments
EValidityStatus FBullCowGame::CheckGuessValidity(FString CurrentGuess)
{
	//Normalize case sensitivity
	FString CorrectedGuess = CaseCorrection(CurrentGuess);

	if (CorrectedGuess.length() != OriginWord.length())	//incorrect Lenght
	{
		return EValidityStatus::IncorrectLenght;
	}
	else if (!bIsIsogram(CorrectedGuess))	// Not isogram
	{
		return EValidityStatus::NotIsogram;
	}

	else if (!bIsAlphabet(CorrectedGuess)) // Non Alphabet symbols
	{
		return EValidityStatus::ContainNonAlphabetCharacter;
	}
	else if (bIsRepeat(CorrectedGuess))
	{
		return EValidityStatus::Repeating;
	}
	else
	{
		return EValidityStatus::OK;
	}

}
//Any answer goes to lower case to provide 100% pure results
FString FBullCowGame::CaseCorrection(FString Guess)
{
	int32 i = 0;
	while (Guess[i])
	{
		FString curChar = Guess.substr(i,1);
		const char *chGuess = curChar.c_str();
		char j = tolower(*chGuess);	
		Guess[i] = j;
		i++;
	}
	return Guess;
}
bool FBullCowGame::bIsRepeat(FString CurrentGuess) const
{

	return false;
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

//validators

bool FBullCowGame::bIsIsogram(FString CurrentGuess) const
{
	TMap<char, bool> isoChecker;

	for (auto Letter : CurrentGuess)
	{
		Letter = tolower(Letter);
		if (isoChecker[Letter])
		{
			return false;
		}
		else
		{
			isoChecker[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::bIsAlphabet(FString CurrentGuess) const
{
	int32 i = 0;
	bool state = true;
	while ( i <= CurrentGuess.length()-1)
	{
		
		FString curChar = CurrentGuess.substr(i, 1);
		const char *chGuess = curChar.c_str();
		int ID = (int)*chGuess;

		if ((ID >= 97) && (ID <= 122))
		{
			state = true;
		}
		else
		{
			state = false;
			break;
		}
		++i;
	}
	return state;
}
// Set Game defaults
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 2;

	GetHiddenWord();
	bIsGameWon = false;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 0; 
}





