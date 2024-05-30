#include "WallSpawner.h"
#include <vector>

AWallSpawner::AWallSpawner(){
	PrimaryActorTick.bCanEverTick = true;

}

void AWallSpawner::BeginPlay(){
	Super::BeginPlay();
	
}

void AWallSpawner::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

FVector AWallSpawner::WallPositionUpdate(FVector PositioningVector, FVector SymbolVector, float WallLength = 0, float WallHeight = 0) {
	return FVector(PositioningVector.X += WallLength * SymbolVector.X, PositioningVector.Y += WallLength * SymbolVector.Y, PositioningVector.Z += WallHeight * SymbolVector.Z);
}

FAEntranceObject AWallSpawner::GenerateEntranceStruct(float NumberOfWalls) {
	FAEntranceObject Entrance;
	Entrance.bWillbeEntrance = bWillbeEntrance();
	Entrance.EntranceId = Entrance.bWillbeEntrance ? FMath::FRandRange(1.f, NumberOfWalls - 1) : -1;
	Entrance.Position = FVector::ZeroVector;
	return Entrance;
}

bool AWallSpawner::bWillbeEntrance() { 
	return FMath::FRandRange(0.f, 1.f) >= 0.5f;
}

TArray<FAEntranceObject> AWallSpawner::CreateWalls(TSubclassOf<AActor> WallClass, TSubclassOf<AActor> EntranceClass, FVector StartLocation, FRotator StartRotation, int32 NumberOfWallsForward, int32 NumberOfWallsRight, float WallLength, float GapBetweenWalls) {
	UWorld* World = GetWorld();
	TArray<FAEntranceObject> EntranceArray;

	if (World and NumberOfWallsForward > 0 and NumberOfWallsRight > 0 and WallLength > 0) {

		FVector SkalarVector[] = { FVector(1.f, 1.f, 0.f), FVector(-0.5f, 0.5f, 0.f), FVector(-0.5f, -0.5f, 0.f), FVector(0.5f, -0.5f, 0.f) };

		for (int32 i = 0; i < 4; i++) {
			EntranceArray.Add(GenerateEntranceStruct(i%2 == 0 ? NumberOfWallsForward : NumberOfWallsRight));
		}

		for (int32 i = 0; i < 4; i++) {
			StartLocation = CreateWallSegment(WallClass, EntranceClass, WallPositionUpdate(StartLocation, SkalarVector[i], i == 0 ? 0.f : WallLength ), StartRotation + FRotator(0.f, 90.f * i, 0.f), i % 2 == 0 ? NumberOfWallsForward : NumberOfWallsRight, WallLength, GapBetweenWalls, EntranceArray[i]);
		}

	}

	return EntranceArray;
}

FVector AWallSpawner::CreateWallSegment(TSubclassOf<AActor> WallClass, TSubclassOf<AActor> EntranceClass, FVector StartLocation, FRotator StartRotation, int32 NumberOfWalls, float WallLength, float GapBetweenWalls, FAEntranceObject &EntranceObject) {
	UWorld* World = GetWorld();
	if (World) {
		FVector SpawnLocation = StartLocation;
		FRotator SpawnRotation = StartRotation;
		bool bEntranceGenerated = false;
		for (int32 i = 0; i < NumberOfWalls; i++) {
			if (!bEntranceGenerated and EntranceObject.bWillbeEntrance and EntranceObject.EntranceId == i) {
				AActor* SpawnedWall = World->SpawnActor<AActor>(EntranceClass, SpawnLocation, SpawnRotation);
				EntranceObject.Position = SpawnLocation, EntranceObject.Rotation = SpawnRotation, bEntranceGenerated = true;
			}
			else {
				AActor* SpawnedWall = World->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);
			}
			if (abs(StartRotation.Roll) == 180 or abs(StartRotation.Roll/i == 0)) {
				SpawnLocation += (WallLength + GapBetweenWalls) * SpawnRotation.Vector();
			}
			else {
				SpawnLocation += (WallLength + GapBetweenWalls) * FRotationMatrix(SpawnRotation).GetScaledAxis(EAxis::X);
			}
		}
		return SpawnLocation;
	}
	return FVector::ZeroVector;
}

TArray<FAEntranceObject> AWallSpawner::CreateCorridors(TSubclassOf<AActor> WallClass, TSubclassOf<AActor> EntranceClass, TSubclassOf<AActor> FloorClass, TArray<FAEntranceObject> EntranceObject, int32 CorridorWalls, float WallLength, float GapBetweenWall) {
	UWorld* World = GetWorld();
	if (World) {
		FAEntranceObject NullObject;
		NullObject.bWillbeEntrance = false;
		FAEntranceObject CorridorObject;
		CorridorObject.bWillbeEntrance = true;
		FVector SkalarVector[] = { FVector(0.5f, 0.5f, 0.f), FVector(-0.5f, 0.5f, 0.f), FVector(-0.5f, -0.5f, 0.f), FVector(0.5f, -0.5f, 0.f) };
		FVector SkalarRight[] = {FVector(400.f, 0.f, 0.f), FVector(0.f, 400.f, 0.f), FVector(-400.f, 0.f, 0.f), FVector(0.f, -400.f, 0.f)};
		for (int32 i = 0; i < 4; i++) {
			if (EntranceObject[i].bWillbeEntrance) {
				FVector StartLocationLeft = WallPositionUpdate(EntranceObject[i].Position, SkalarVector[i], -WallLength);
				FVector StartLocationRight = StartLocationLeft + SkalarRight[i];
				FRotator LeftRotation = EntranceObject[i].Rotation + FRotator(0.f, 90.f, 0.f);
				FRotator RightRotation = EntranceObject[i].Rotation + FRotator(0.f, -90.f, 0.f);
				//StartLocationRight + SkalarRight[i];
				for (int32 j = 0; j < CorridorWalls; j++) {
					StartLocationLeft = CreateWallSegment(WallClass, EntranceClass, StartLocationLeft, LeftRotation, 1, -WallLength, GapBetweenWall, NullObject);
				}

				for (int32 j = 0; j < CorridorWalls; j++) {
					StartLocationRight = CreateWallSegment(WallClass, EntranceClass, StartLocationRight, LeftRotation, 1, -WallLength, GapBetweenWall, NullObject);
				}
			}
		}
	}
	return EntranceObject;
}

void AWallSpawner::DebugPrintEntranceArray(TArray<FAEntranceObject> Object) {
	for (const FAEntranceObject& element : Object) {
		FString DebugMessage = FString::Printf(TEXT("Entrance Id: %d, bWillbeEntrance: %s, Position: (%f, %f, %f), Rotation: (%f, %f, %f)"), element.EntranceId, element.bWillbeEntrance ? TEXT("Yes") : TEXT("No"), element.Position.X, element.Position.Y, element.Position.Z, element.Rotation.Pitch, element.Rotation.Roll, element.Rotation.Yaw);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DebugMessage);
	}
}

void AWallSpawner::DebugPrintVectorArray(TArray<FVector> Object) {
	for (const FVector& element : Object) {
		FString DebugMessage = FString::Printf(TEXT("Value: (%f, %f, %f)"), element.X, element.Y, element.Z);
		GEngine->AddOnScreenDebugMessage(-1, -5.f, FColor::Red, DebugMessage);
	}
}
