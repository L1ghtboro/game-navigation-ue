#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallSpawner.h"

#include "RoomSpawner.generated.h"


UCLASS() class DUNGEONPROCEDURAL_API ARoomSpawner : public AWallSpawner {
	GENERATED_BODY()
	
public:	
	ARoomSpawner();
	
	UFUNCTION(BlueprintCallable, Category = "Floor Spawner")
	void CreateFloor(TSubclassOf<AActor> FloorClass, FVector StartLocation, FRotator StartRotation, int32 NumberOfWallsForward, int32 NumberOfWallsRight, float WallLength);

	UFUNCTION(BlueprintCallable, Category = "Floor Spawner")
	void CreateFloorCorridors(TSubclassOf<AActor> FloorClass, FAEntranceObject EntranceObject, int32 NumberOfWallsForward, float WallLength);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
