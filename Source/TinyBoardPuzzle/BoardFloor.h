// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardFloor.generated.h"


class UMaterial;

UCLASS()
class TINYBOARDPUZZLE_API ABoardFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	UMaterial* FloorMat1;

	UPROPERTY(EditAnywhere)
	UMaterial* FloorMat2;

	// Red material
	UPROPERTY(EditAnywhere)
	UMaterial* FloorMatDenied;	

	// 2D Floor Coordinates
	UPROPERTY(VisibleAnywhere)
	FVector2D FloorCoord;

	// Set default material of the board floor piece (black or white)
	UFUNCTION()
    void SetDefaultMaterial(const int32& Index);	

private:

	// Cached default material
	UPROPERTY()
	UMaterial* DefaultMat;

public:		
	UFUNCTION()
	void Init(const FVector2D Coord);

	// This function changes the default floor material to red material according to the provided bool.
	UFUNCTION()
    void ChangeCurrentMaterial(const bool& bIsDenied) const;

};
