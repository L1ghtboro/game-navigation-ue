#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallSpawner.generated.h"

USTRUCT(BlueprintType) struct FAEntranceObject {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 EntranceId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bWillbeEntrance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Position;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator Rotation;
};

UCLASS()
class DUNGEONPROCEDURAL_API AWallSpawner : public AActor{
	GENERATED_BODY()
	
public:	
	AWallSpawner();

	UFUNCTION(BlueprintCallable, Category = "Wall Spawner")
	TArray<FAEntranceObject> CreateWalls(TSubclassOf<AActor> WallClass, TSubclassOf<AActor> EntranceClass, FVector StartLocation, FRotator StartRotation, int32 NumberOfWallsForward, int32 NumberOfWallsRight, float WallLength, float GapBetweenWalls);

	UFUNCTION(BlueprintCallable, Category = "Corridor Spawner")
	TArray<FAEntranceObject> CreateCorridors(TSubclassOf<AActor> WallClass, TSubclassOf<AActor> EntranceClass, TSubclassOf<AActor> FloorClass, TArray<FAEntranceObject> EntranceObject, int32 CorridorWalls, float WallLength, float GapBetweenWall);

	UFUNCTION(BlueprintCallable, Category = "Debug Printer")
	void DebugPrintEntranceArray(TArray<FAEntranceObject> Object);

	UFUNCTION(BlueprintCallable, Category = "Debug Printer")
	void DebugPrintVectorArray(TArray<FVector> Object);

	UFUNCTION(BlueprintCallable, Category = "Getter FAEntranceObject")
	FVector GetEntrancePosition(FAEntranceObject Object) { return Object.Position; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(BlueprintCallable, Category = "Wall Updater")
	FVector WallPositionUpdate(FVector PositioningVector, FVector SymbolVector, float WallLength, float WallHeight);

	UFUNCTION(BlueprintCallable, Category = "Wall Spawner")
	FVector CreateWallSegment(TSubclassOf<AActor> WallClass, TSubclassOf<AActor> EntranceClass, FVector StartLocation, FRotator StartRotation, int32 NumberOfWalls, float WallLength, float GapBetweenWalls, FAEntranceObject &Object);

	UFUNCTION(BlueprintCallable, Category = "Entrance Generator")
	FAEntranceObject GenerateEntranceStruct(float NumberOfWalls);

	UFUNCTION(BlueprintCallable, Category = "Entrance Generator")
	bool bWillbeEntrance();
};
