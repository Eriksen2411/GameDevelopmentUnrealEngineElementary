// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "WordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    InitGame();

    // PrintLine(TEXT("Debug. Word %s, Length %i"), *HiddenWord, HiddenWord.Len());

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        InitGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = Words[FMath::RandRange(0, Words.Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to the game!"));
    PrintLine(TEXT("Guess the word with %i chars!"), Lives);
    PrintLine(TEXT("You have %i lives left"), Lives);
    PrintLine(TEXT("Press enter to check guess..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again...."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT(""));
        PrintLine(TEXT("Correct guess"));
        PrintLine(TEXT("You win the game"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The guessing word must have %i chars\nTry guessing again"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The guessing word must be an isogram\nTry guessing again"), HiddenWord.Len());
        return;
    }

    --Lives;

    if (Lives > 0)
    {
        int32 Bulls, Cows;
        GetBullsCows(Guess, Bulls, Cows);

        PrintLine(TEXT("Your guess has %i Bulls and %i Cows"), Bulls, Cows);
        PrintLine(TEXT("Incorrect guess. You have %i lives left."), Lives);
    }
    else
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left."));
        PrintLine(TEXT("The hidden word is %s"), *HiddenWord);
        EndGame();
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 WordLength = Word.Len();
    for (int i = 0; i < WordLength; i++)
    {
        for (int j = i + 1; j < WordLength; j++)
        {
            if (Word[i] == Word[j])
            {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::GetBullsCows(const FString& Guess, int32& Bulls, int32& Cows) const
{
    Bulls = 0;
    Cows = 0;

    for (int i = 0; i < Guess.Len(); i++)
    {
        if (Guess[i] == HiddenWord[i])
        {
            Bulls++;
            continue;
        }
        else
        {
            for (int j = 0; j < HiddenWord.Len(); j++)
            {
                if (Guess[i] == HiddenWord[j])
                {
                    Cows++;
                    break;
                }
            }
        }
    }
}