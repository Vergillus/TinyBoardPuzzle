// Copyright Epic Games, Inc. All Rights Reserved.


#include "TinyBoardPuzzleGameModeBase.h"


#include "BoardPiece.h"
#include "Kismet/GameplayStatics.h"

void ATinyBoardPuzzleGameModeBase::BeginPlay()
{
    Super::BeginPlay();    
    
    UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = true;
    UGameplayStatics::GetPlayerController(GetWorld(),0)->bEnableClickEvents = true;
    UGameplayStatics::GetPlayerController(GetWorld(),0)->bEnableMouseOverEvents = true;

    UGameplayStatics::GetPlayerController(GetWorld(),0)->ClickEventKeys.Add(EKeys::RightMouseButton);
    
}

int32 ATinyBoardPuzzleGameModeBase::GetTotalPieceNumber()
{
    return ABoardPiece::TotalPieceCount;
}

void ATinyBoardPuzzleGameModeBase::UpdateUI_Implementation()
{
}

void ATinyBoardPuzzleGameModeBase::GameOver_Implementation()
{
}

void ATinyBoardPuzzleGameModeBase::GameOverCheck_Implementation()
{
    if (ABoardPiece::TotalPieceCount == 0)
    {
        GameOver();
        //GEngine->AddOnScreenDebugMessage(0,10,FColor::Emerald,FString("Game Over"));
    }
    else
    {
        UpdateUI();
    }
}
