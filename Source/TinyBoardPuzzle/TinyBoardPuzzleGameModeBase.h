// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TinyBoardPuzzleGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TINYBOARDPUZZLE_API ATinyBoardPuzzleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void GameOverCheck();

	UFUNCTION(BlueprintNativeEvent)
	void GameOver();

	UFUNCTION(BlueprintNativeEvent)
	void UpdateUI();

	UFUNCTION(BlueprintPure)
	static int32 GetTotalPieceNumber();
	
};
