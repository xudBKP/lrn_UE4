// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The number of possible words is %i"), Words.Num());

    // PrintLine(TEXT("The Hidden Word is: %s. \nIt is %i characters long"), *HiddenWord, HiddenWord.Len());

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
    
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to Bull Cows!"));
    
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type your guess and \npress enter to contune..."));

    IsIsogram(HiddenWord);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("\nPress enter to play agian."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if(Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
        return;
    }
    
    //check if isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }
    //remove lives
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("\nThe hidden word is %s"), *HiddenWord);
        
        EndGame();
        return;
    }
    //show player bull and cows
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);

}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 comparison = Index+1; comparison < Word.Len(); comparison++)
        {
            if(Word[Index] == Word[comparison])
            {
                return false;
            }
        }
        
    }

    return true;
    
}

