// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectSpawner.generated.h"

UCLASS()
class DUNGEONPROCEDURAL_API AObjectSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectSpawner();

	UFUNCTION(BlueprintCallable, Category = "Debug Spawner")
	void SpawnObject(TSubclassOf<AActor> ObjectToSpawn, int32 NumObjects);

	UFUNCTION(BlueprintCallable, Category = "Debug Spawner")
	void CreateRoom(TSubclassOf<AActor> Floor, TSubclassOf<AActor> Walls);

	UFUNCTION(BlueprintCallable, Category = "Debug Wall Spawner")
	void SpawnWall(const FVector& FloorMin, const FVector& FloorMax, TSubclassOf<AActor> Wall, const FVector& WallScale);

	UFUNCTION(BlueprintCallable, Category = "Debug Wall Spawner")
	void SpawnWallSegment(const FVector& Start, const FVector& End, TSubclassOf<AActor> Wall, const FVector& WallScale);

	UFUNCTION(BlueprintCallable, Category = "Debug Wall Spawner")
	FVector SpawnWalls(TSubclassOf<AActor> Wall, int32 MinNumberOfWalls, int32 MaxNumberOfWalls, float WallLength, float GapBetweenWalls);

	UFUNCTION(BlueprintCallable, Category = "Debug Wall Spawner")
	void SpawnCornerWall(TSubclassOf<AActor>Wall, FVector StartPosition, FRotator WallRotation, float WallLength);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
