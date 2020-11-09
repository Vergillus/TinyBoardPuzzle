// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardCreator.generated.h"

UCLASS()
class TINYBOARDPUZZLE_API ABoardCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sıze of the board. Default is 8x8
	UPROPERTY()
	int32 BoardSize;

	// Size of a single board cell.
	UPROPERTY()
	int32 CellSize;

	//UPROPERTY()
	//class UInstancedStaticMeshComponent* InstancedStaticMesh;


	// Board Piece to spawn
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class ABoardPiece> BoardPiece;

	// Board Floor to spawn
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class ABoardFloor> BoardFloor;	

	// This array holds the one dimensional indexes of two dimensional coordinates.	
	UPROPERTY()
	TArray<int32> RedFloorPieceIndexes;

	// Container of all board floors that spawned.
	UPROPERTY()
	TArray<class ABoardFloor*> Floors;

	// This function creates board and for all board floor creates hıdden a piece
	UFUNCTION()
	void CreateBoard();

	// This function converts 2D Coordinates to 1D array index
	int32 IndexFrom2DCoords(const FVector2D& Coord) const;

	// This functions spawn red floor board that indicates that specific area of the board is forbidden
	UFUNCTION()
	void SpawnRedBoardFloor(ABoardPiece* AttachTo, const FVector& SpawnLoc);

	// This function checks the provided 2D map coordinate whether it is inside the board grid or not.
	UFUNCTION()
	bool BoundaryCheck(const FVector2D MapCoordinate);

	// This function checks the diagonal of the given map coordinate
	void CheckDiagonal(FVector2D MapCoordinate, const int32& X, const int32& Y,const int32& MapValue, ABoardPiece* AttachTo);

	// This function destroys the corresponded red floor boards.
	void RemoveRedFloorIndexes(const int32& Index);

	// Positional offset for red floor pieces 
	FVector RedPiecePosOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// This function checks the given map coord ıs reachable.
	bool CheckMap(const FVector2D& MapCoord) const;	

	// This function is for applying the rules of the game.
	void ChangeMapRules(const FVector2D& Coord, ABoardPiece* P, const int32& Val);

};
