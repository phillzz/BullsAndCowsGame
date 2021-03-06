// BullCowGame.cpp : Defines the entry point for the console application.
#pragma once

#include "stdafx.h"
// Unreal Engine standarts
using FText = std::string;
using int32 = int;
// Main workflow function declaration
void PrintIntro(); 
void PlayGame();

void PrintResults(bool);
bool AskToPlayAgain();
FText GetValidGuess();
//Create game Instance
FBullCowGame BCGame;

int main()
{
	bool bPlayGame = false;
	// Game Loop
	do 
	{
		PrintIntro();
		PlayGame();
		bPlayGame = AskToPlayAgain();
	} while (bPlayGame == true);

	// exit application
	return 0;
}
//Main workflow function defenition
void PlayGame()
{
	//Instantiate a new game
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = GetValidGuess();
	// Ask number of turns times for a guess
		while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) // for (int32 i = 0; i < MaxTries; i++)
		{
			SBullCowCount BCCount = BCGame.SetGuess(Guess);
			
			if (BCGame.IsGameWon())
			{
				//break;
			}
			else if (BCGame.GetCurrentTry() <= MaxTries)
			{
				std::cout << "Your guess was: " << Guess << std::endl;
				
				std::cout << "Bulls = " << BCCount.Bulls;
				std::cout << ". Cows = " << BCCount.Cows << std::endl;
				std::cout << std::endl;
				
				Guess = GetValidGuess();
			}

		}
	// TODO: summarize results
	PrintResults(BCGame.IsGameWon());
}
//Print on screen game intro  
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows - a great word game!" << std::endl;
	std::cout << "Guess the " << BCGame.GetHiddenWordLenght() << " letter isogram that i'm thinking of" << std::endl;
	std::cout << std::endl;
	return;
}
//Check Guess for validity and return a valid result or ask for guess again.
FText GetValidGuess()
{
	EValidityStatus Status = EValidityStatus::Invalid_Status;
	FText GUESS = "";
	//If guess not valid ask to try again
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, GUESS);
		//std::cout << std::endl;

		FString CorrectedGuess = BCGame.CaseCorrection(GUESS);
		Status = BCGame.CheckGuessValidity(GUESS);
		switch (Status)
		{
		case EValidityStatus::IncorrectLenght:std::cout << "MiSTAKE! Incorrect Guess lenght!\n";
			break;
		case EValidityStatus::NotIsogram: std::cout << "MiSTAKE! It is not Isogram!\n";
			break;
		case EValidityStatus::ContainNonAlphabetCharacter: std::cout << "MiSTAKE! You should use only letters\n";
			break;
		case EValidityStatus::OK:
			break;
		case EValidityStatus::Repeating: std::cout << "MISTAKE! You already tried " << CorrectedGuess << " before!\n";
			break;
		default:
			return CorrectedGuess;
		}
		std::cout << std::endl;
	} while (Status != EValidityStatus::OK);
	//return valid guess
	return BCGame.CaseCorrection(GUESS);
}
void PrintResults(bool state)
{
	if (!state) 
	{
		std::cout << "You Lose!" << std::endl;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Correct! You Win! Right answer is: " << BCGame.GetHiddenWord() << std::endl;
		std::cout << "You guess it on #" << BCGame.GetCurrentTry() << " step. " << std::endl;
		std::cout << std::endl;
	}
}
//Ask to play again
bool AskToPlayAgain()
{ 
	std::cout << "Do you want to play again? (y/n): ";
	FText Responce = "";
	std::getline(std::cin, Responce);
	std::cout << std::endl;
	return (Responce[0] == 'Y') || (Responce[0] == 'y');
}


