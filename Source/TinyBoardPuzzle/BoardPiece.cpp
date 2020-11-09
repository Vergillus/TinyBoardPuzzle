// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardPiece.h"

#include "BoardCreator.h"
#include "TinyBoardPuzzleGameModeBase.h"

#include "Kismet/GameplayStatics.h"


int32 ABoardPiece::TotalPieceCount = 8;

// Sets default values
ABoardPiece::ABoardPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	RootComponent = StaticMesh;	
}

// Called when the game starts or when spawned
void ABoardPiece::BeginPlay()
{
	Super::BeginPlay();

	PieceOwner = Cast<ABoardCreator>(GetOwner());

	GameModeBase = Cast<ATinyBoardPuzzleGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void ABoardPiece::NotifyActorOnClicked(FKey ButtonPressed)
{

	// If left mouse button is clicked set the board piece visible, change its material and spawn new board piece for visual aid
	if(ButtonPressed == EKeys::LeftMouseButton)
	{
		if (BCanPlaceThePiece && TotalPieceCount > 0 && !bIsPlaced)
		{
			bIsPlaced = true;

			PieceOwner->ChangeMapRules(Coord,this, 1);
			StaticMesh->SetMaterial(0, MouseClickedMat);
			TotalPieceCount--;
			
			if (GameModeBase)
			{
				GameModeBase->GameOverCheck();
			}
		}
	}
	// If right mouse is clicked set the board piece hidden and destroy all visual aid.
	else if (ButtonPressed == EKeys::RightMouseButton)
	{
		if (bIsPlaced)
		{
			bIsPlaced = false;

			StaticMesh->SetMaterial(0, MouseOverMat);

			TArray<AActor*> AttachedActors;

			GetAttachedActors(AttachedActors);

			for (AActor* Element : AttachedActors)
			{
				Element->Destroy();
			}

			PieceOwner->ChangeMapRules(Coord, this, 0);

			TotalPieceCount++;

			if (GameModeBase)
			{
				GameModeBase->GameOverCheck();
			}
		}
	}
}

void ABoardPiece::NotifyActorBeginCursorOver()
{
	if(bIsPlaced) return;

	if (PieceOwner->CheckMap(Coord))
	{
		StaticMesh->SetMaterial(0, MouseOverDeniedMat);
		BCanPlaceThePiece = false;
	}
	else
	{
		StaticMesh->SetMaterial(0, MouseOverMat);
		BCanPlaceThePiece = true;
	}

	StaticMesh->ToggleVisibility();
}

void ABoardPiece::NotifyActorEndCursorOver()
{
	if(bIsPlaced) return;
	
	StaticMesh->ToggleVisibility();
}

void ABoardPiece::Init(const FVector2D& InCoord)
{
	Coord = InCoord;	
}

// Called every frame
void ABoardPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

