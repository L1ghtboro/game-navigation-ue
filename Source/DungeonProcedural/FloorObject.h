
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorObject.generated.h"

UCLASS() class DUNGEONPROCEDURAL_API AFloorObject : public AActor{
	GENERATED_BODY()
	
public:	
	AFloorObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Procedural Meshes") 
	class UStaticMeshComponent* FloorMeshComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
