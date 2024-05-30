// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"

// Sets default values
AObjectSpawner::AObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObjectSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectSpawner::SpawnObject(TSubclassOf<AActor> ObjectToSpawn, int32 NumberObjects)
{
	if (ObjectToSpawn != nullptr) {
		UWorld* World = GetWorld();
		if (World) 
		{
			for (int32 i = 0; i < NumberObjects; i++) 
			{
				//FVector SpawnLocation = FMath::RandPointInBox(FBox(FVector(-1000.f, -1000.f, -1000.f), FVector(1000.f, 1000.f, 1000.f)));
				FVector SpawnLocation = FVector(FMath::FRandRange(-1000.f, 1000.f), FMath::FRandRange(-1000.f, 1000.f), 50.f);
				FRotator SpawnRotation = FRotator::ZeroRotator;

				AActor* SpawnedObject = World->SpawnActor<AActor>(ObjectToSpawn, SpawnLocation, SpawnRotation);
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Spawned"));
			}
		}
	}
}

void AObjectSpawner::CreateRoom(TSubclassOf<AActor> Floor, TSubclassOf<AActor> Walls)
{
	if (Floor != nullptr and Walls != nullptr) {
		UWorld* World = GetWorld();
		if (World)
		{
			float FloorWidth = FMath::FRandRange(5.f, 12.f);
			float FloorLength = FMath::FRandRange(5.f, 12.f);

			FVector FloorLocation = FVector(0.f, 0.f, 0.f);
			FRotator FloorRotation = FRotator::ZeroRotator;
			AActor* SpawnedFloor = World->SpawnActor<AActor>(Floor, FloorLocation, FloorRotation);

			if (SpawnedFloor)
			{
				SpawnedFloor->SetActorScale3D(FVector(FloorWidth, FloorLength, 1.0f));

				FVector FloorMin, FloorMax;
				SpawnedFloor->GetActorBounds(false, FloorMin, FloorMax);

				FVector WallScale = FVector(1.0f, 1.0f, 1.0f);
				SpawnWall(FloorMin, FloorMax, Walls, WallScale);
			}
		}
	}
}

void AObjectSpawner::SpawnWall(const FVector& FloorMin, const FVector& FloorMax, TSubclassOf<AActor> WallClass, const FVector& WallScale)
{
    UWorld* World = GetWorld();
    if (World)
    {
        // Bottom wall
        SpawnWallSegment(FVector(FloorMin.X, -FloorMax.Y, FloorMin.Z + WallScale.Z / 2), FVector(FloorMax.X, -FloorMax.Y, FloorMin.Z + WallScale.Z / 2), WallClass, WallScale);
        // Top wall
        SpawnWallSegment(FVector(FloorMin.X, FloorMax.Y, FloorMin.Z + WallScale.Z / 2), FVector(FloorMax.X, FloorMax.Y, FloorMin.Z + WallScale.Z / 2), WallClass, WallScale);
        // Left wall
        SpawnWallSegment(FVector(-FloorMax.X, FloorMin.Y, FloorMin.Z + WallScale.Z / 2), FVector(-FloorMax.X, FloorMax.Y, FloorMin.Z + WallScale.Z / 2), WallClass, WallScale);
        // Right wall
        SpawnWallSegment(FVector(FloorMax.X, FloorMin.Y, FloorMin.Z + WallScale.Z / 2), FVector(FloorMax.X, FloorMax.Y, FloorMin.Z + WallScale.Z / 2), WallClass, WallScale);
    }
}

void AObjectSpawner::SpawnWallSegment(const FVector& Start, const FVector& End, TSubclassOf<AActor> WallClass, const FVector& WallScale)
{
	UWorld* World = GetWorld();
	if (World)
	{
		// Calculate the midpoint of the wall segment
		FVector WallLocation = (Start + End) / 2;

		// Calculate the direction of the wall segment
		FVector WallDirection = (End - Start).GetSafeNormal();

		// Calculate the length of the wall segment
		float WallLength = (End - Start).Size();

		// Calculate the rotation of the wall segment
		FRotator Rotation = WallDirection.Rotation();

		// Spawn the wall segment
		AActor* SpawnedWall = World->SpawnActor<AActor>(WallClass, WallLocation, Rotation);
		if (SpawnedWall)
		{
			// Scale the wall segment to match its length
			SpawnedWall->SetActorScale3D(FVector(WallLength / 200, WallScale.Y, WallScale.Z)); // Adjust scale as needed

			// Adjust the position to center-align the wall segment
			FVector Offset = WallDirection * (WallLength / 2);
			SpawnedWall->SetActorLocation(WallLocation - Offset);
		}
	}
}

FVector AObjectSpawner::SpawnWalls(TSubclassOf<AActor> WallClass, int32 MinNumberOfWalls, int32 MaxNumberOfWalls, float WallLength, float GapBetweenWalls){
	if (WallClass and MinNumberOfWalls and MaxNumberOfWalls and WallLength) {
		UWorld* World = GetWorld();
		if (World) {
			FVector StartLocation = FVector(0.f, 0.f, 0.f);
			FVector SpawnLocation = StartLocation;
			int32 NumberOfWalls = FMath::FRandRange(static_cast<float>(MinNumberOfWalls), static_cast<float>(MaxNumberOfWalls));

			FRotator SpawnRotation = FRotator::ZeroRotator;
			for (int32 i = 0; i < NumberOfWalls; i++) {
				AActor* SpawnedWall = World->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);
				SpawnLocation += (WallLength + GapBetweenWalls) * GetActorForwardVector();
			}

			return SpawnLocation;
		}
	}
	return FVector::ZeroVector;
}

void AObjectSpawner::SpawnCornerWall(TSubclassOf<AActor>Wall, FVector StartPosition, FRotator WallRotation, float WallLength){
	if (Wall and WallLength) {
		UWorld* World = GetWorld();
		if (World) {
			FVector EndPosition = StartPosition + (WallLength * GetActorRightVector());
			EndPosition.X -= WallLength / 2;
			EndPosition.Y /= 2;
			AActor* SpawnerCornerWall = World->SpawnActor<AActor>(Wall, EndPosition, WallRotation);
		}
	}
}