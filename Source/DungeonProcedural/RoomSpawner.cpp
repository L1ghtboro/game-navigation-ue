#include "RoomSpawner.h"

ARoomSpawner::ARoomSpawner(){
	PrimaryActorTick.bCanEverTick = true;
}

void ARoomSpawner::BeginPlay(){
	Super::BeginPlay();
}

void ARoomSpawner::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ARoomSpawner::CreateFloor(TSubclassOf<AActor> FloorClass, FVector StartLocation, FRotator StartRotation, int32 NumberOfWallsForward, int32 NumberOfWallsRight, float WallLength) {
	UWorld* World = GetWorld();
	if (World) {
		float FloorWidth = NumberOfWallsForward;
		float FloorLength = NumberOfWallsRight;

		AActor* SpawnedFloor = World->SpawnActor<AActor>(FloorClass, FVector(NumberOfWallsForward * WallLength / 2 - WallLength / 2 + StartLocation.X, NumberOfWallsRight * WallLength / 2 + StartLocation.Y, StartLocation.Z) , StartRotation);

		if (SpawnedFloor) {
			SpawnedFloor->SetActorScale3D(FVector(FloorWidth, FloorLength, 1.f));
		}
	}
}

void ARoomSpawner::CreateFloorCorridors(TSubclassOf<AActor> FloorClass, FAEntranceObject EntranceObject, int32 NumberOfWalls, float WallLength) {
	UWorld* World = GetWorld();
	if (World) {
		FString RotationString = EntranceObject.Rotation.ToString();
		if (EntranceObject.bWillbeEntrance) {
			switch (static_cast<int>(EntranceObject.Rotation.Yaw)) {
			case 0:
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("1"));
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Rotation: %s"), *RotationString));
				CreateFloor(FloorClass, EntranceObject.Position - FVector((WallLength * (NumberOfWalls - 1)) / 2, (WallLength * (NumberOfWalls + 1)) / 2, 0.f), EntranceObject.Rotation + FRotator(0.f, 90.f, 0.f), NumberOfWalls, 1, WallLength);
				break;
			case 90:
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("2"));
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Rotation: %s"), *RotationString));
				CreateFloor(FloorClass, EntranceObject.Position + FVector((WallLength * (NumberOfWalls - 2)) / 2, (WallLength * (NumberOfWalls - 4)) / 2, 0.f), EntranceObject.Rotation + FRotator(0.f, 90.f, 0.f), NumberOfWalls, 1, WallLength);
				break;
			case 180:
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("3"));
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Rotation: %s"), *RotationString));
				CreateFloor(FloorClass, EntranceObject.Position - FVector((WallLength * (NumberOfWalls + 2)) / 2, (WallLength * (NumberOfWalls + 3)) / 2, 0.f), EntranceObject.Rotation + FRotator(0.f, 0.f, 0.f), 1, NumberOfWalls, WallLength);
				break;
			case 270:
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("4"));
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Rotation: %s"), *RotationString));
				CreateFloor(FloorClass, EntranceObject.Position, EntranceObject.Rotation + FRotator(0.f, 90.f, 0.f), 1, NumberOfWalls, WallLength);
				break;
			}
		}
	}
}
//
//UWorld* World = GetWorld();
//if (World) {
//	if (EntranceObject.bWillbeEntrance) {
//		FVector StartLocation = EntranceObject.Position;
//		FRotator StartRotatation = EntranceObject.Rotation;
//
//		AActor* SpawnedFloor = World->SpawnActor<AActor>(FloorClass, StartLocation, StartRotatation);
//
//		if (SpawnedFloor) {
//			SpawnedFloor->SetActorScale3D(FVector(NumberOfWalls, NumberOfWalls, 0.f));
//		}
//	}
//}