// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardFloor.h"

// Sets default values
ABoardFloor::ABoardFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Floor"));

	RootComponent = StaticMesh;	

}

// Called when the game starts or when spawned
void ABoardFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABoardFloor::SetDefaultMaterial(const int32& Index)
{
	if(!StaticMesh) return;

	UMaterial* TmpMat = (Index % 2 == 0) ? FloorMat1 : FloorMat2;

	if(TmpMat)
	{
		StaticMesh->SetMaterial(0,TmpMat);

		DefaultMat = TmpMat;		
	}
	
}

void ABoardFloor::ChangeCurrentMaterial(const bool& bIsDenied) const
{
	if (bIsDenied)
	{
		StaticMesh->SetMaterial(0,FloorMatDenied);
	}
	else
	{
		StaticMesh->SetMaterial(0,DefaultMat);
	}
}

void ABoardFloor::Init(const FVector2D Coord)
{
	FloorCoord = Coord;

	SetDefaultMaterial(FloorCoord.X + FloorCoord.Y);	
}


