// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "BoardPiece.generated.h"

UCLASS()
class TINYBOARDPUZZLE_API ABoardPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* MouseOverMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* MouseOverDeniedMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterial* MouseClickedMat;

	// on Clicked Event
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	// on Mouse Over Event
	virtual void NotifyActorBeginCursorOver() override;

	// on Mouse Over Event End
	virtual void NotifyActorEndCursorOver() override;

	// The owner of the piece. The Actor that spawns this actor
	class ABoardCreator* PieceOwner;

	// 2D Coordinates. Initialized after the spawn
	UPROPERTY()
	FVector2D Coord;

	UPROPERTY()
	int32 PieceId;

	UPROPERTY()
	bool BCanPlaceThePiece;

	UPROPERTY()
	bool bIsPlaced;

	UPROPERTY()
	class ATinyBoardPuzzleGameModeBase* GameModeBase;	

private:	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return StaticMesh;}

	void Init(const FVector2D& InCoord);

	static int32 TotalPieceCount;

};
