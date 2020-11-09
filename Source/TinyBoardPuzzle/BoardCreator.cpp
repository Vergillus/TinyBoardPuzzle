// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardCreator.h"

#include "BoardPiece.h"

#include "BoardFloor.h"

// Sets default values
ABoardCreator::ABoardCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced Static Mesh"));

	//RootComponent = InstancedStaticMesh;

	BoardSize = 8;
	CellSize = 100;
	
}

// Called when the game starts or when spawned
void ABoardCreator::BeginPlay()
{
	Super::BeginPlay();
				  
	CreateBoard();

	RedPiecePosOffset = FVector::UpVector * 1.5f;
}                 
				  
// Called every frame
void ABoardCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABoardCreator::CheckMap(const FVector2D& MapCoord) const
{
	
	const int32 TmpIndex = IndexFrom2DCoords(MapCoord);	
	
	return RedFloorPieceIndexes.Contains(TmpIndex); //(bool)MapCheck[TmpIndex];
}

void ABoardCreator::ChangeMapRules(const FVector2D& Coord, ABoardPiece* P, const int32& Val)
{

	if(Val > 0)	// Spawn additional floor tiles and Set MapCheck array value to 1
	{
		// Horizontal
		for (int X = 0; X < BoardSize; ++X)
		{
			const int32 TmpIndex = IndexFrom2DCoords(FVector2D(X,Coord.Y));

			RedFloorPieceIndexes.Add(TmpIndex);
		
			SpawnRedBoardFloor(P,Floors[TmpIndex]->GetActorLocation() + RedPiecePosOffset);
		}

		//Vertical
		for (int Y = 0; Y < BoardSize; ++Y)
		{
			const int32 TmpIndex = IndexFrom2DCoords(FVector2D(Coord.X,Y));

			RedFloorPieceIndexes.Add(TmpIndex);			
		
			SpawnRedBoardFloor(P,Floors[TmpIndex]->GetActorLocation() + RedPiecePosOffset);
		}

		
		// Diagonals
		///////////////////////
		// Bottom Left
		CheckDiagonal(Coord,-1,-1,1,P);
		// Bottom Right
		CheckDiagonal(Coord,-1,1,1,P);
		// Top Left
		CheckDiagonal(Coord,1,-1,1,P);
		// Top Right
		CheckDiagonal(Coord,1,1,1,P);
		////////////////////////////////
		
	}
		
	else	// Remove red floor indexes from RedFloorPieceIndexes array for all directions
	{
		// Horizontal
		for (int X = 0; X < BoardSize; ++X)
		{
			const int32 TmpIndex = IndexFrom2DCoords(FVector2D(X,Coord.Y));

			RemoveRedFloorIndexes(TmpIndex);
		}

		//Vertical
		for (int Y = 0; Y < BoardSize; ++Y)
		{
			const int32 TmpIndex = IndexFrom2DCoords(FVector2D(Coord.X,Y));					
		
			RemoveRedFloorIndexes(TmpIndex);
		}

		
		// Diagonals
		///////////////////////
		// Bottom Left
		CheckDiagonal(Coord,-1,-1,0,P);
		// Bottom Right
		CheckDiagonal(Coord,-1,1,0,P);
		// Top Left
		CheckDiagonal(Coord,1,-1,0,P);
		// Top Right
		CheckDiagonal(Coord,1,1,0,P);
		////////////////////////////////		
	}
	
}

void ABoardCreator::SpawnRedBoardFloor(ABoardPiece* AttachTo, const FVector& SpawnLoc)
{
	// Spawn a floor board actor
	ABoardFloor* Tmp = GetWorld()->SpawnActor<ABoardFloor>(BoardFloor,SpawnLoc, FRotator::ZeroRotator);

	// Set its material to red material
	Tmp->ChangeCurrentMaterial(true);

	// Attach to the board piece that spawns this floor actor
	Tmp->AttachToActor(AttachTo,FAttachmentTransformRules::KeepWorldTransform);		
}

bool ABoardCreator::BoundaryCheck(const FVector2D MapCoordinate)
{
	return (MapCoordinate.X < BoardSize && MapCoordinate.X >= 0)  &&  (MapCoordinate.Y < BoardSize && MapCoordinate.Y >= 0);
}

void ABoardCreator::CheckDiagonal(FVector2D MapCoordinate, const int32& X, const int32& Y, const int32& MapValue, ABoardPiece* AttachTo)
{
	while (BoundaryCheck(MapCoordinate))
	{		
		const int32 TmpIndex = IndexFrom2DCoords(MapCoordinate);

		if(MapValue == 1)
		{
			RedFloorPieceIndexes.Add(TmpIndex);
			SpawnRedBoardFloor(AttachTo,Floors[TmpIndex]->GetActorLocation() + RedPiecePosOffset);
		}
		else if(MapValue == 0)
		{
			RemoveRedFloorIndexes(TmpIndex);
		}
		MapCoordinate.X = MapCoordinate.X + X;
		MapCoordinate.Y = MapCoordinate.Y + Y;
	}
}

void ABoardCreator::RemoveRedFloorIndexes(const int32& Index)
{
	if (RedFloorPieceIndexes.Contains(Index))
	{
		RedFloorPieceIndexes.RemoveAt(RedFloorPieceIndexes.Find(Index));
	}
}

int32 ABoardCreator::IndexFrom2DCoords(const FVector2D& Coord) const
{
	return Coord.X * BoardSize + Coord.Y;
}

void ABoardCreator::CreateBoard() 
{
	UWorld* const World = GetWorld();

	const FRotator Rot = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;	

	for (int32 X = 0; X < BoardSize; ++X)
	{
		for (int32 Y = 0; Y < BoardSize; ++Y)
		{
			if(World)
			{
				FVector Location = FVector(X * CellSize, Y*CellSize,0);
	
				FVector2D Coord(X,Y);

				// Spawn a board piece actor
				ABoardPiece* Piece = World->SpawnActor<ABoardPiece>(BoardPiece,Location,Rot,SpawnParams);

				if(Piece)
				{
					Piece->GetMeshComponent()->SetVisibility(false);
					Piece->Init(Coord);	
				}				

				// Spawn a board floor actor and populate Floors array
				ABoardFloor* Floor = World->SpawnActor<ABoardFloor>(BoardFloor,Location,Rot,SpawnParams);

				if (Floor)
				{
					Floor->Init(Coord);				
					Floors.Add(Floor);	
				}				
			}
		}
	}	
}







