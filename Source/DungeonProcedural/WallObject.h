#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallObject.generated.h"

UCLASS() class DUNGEONPROCEDURAL_API AWallObject : public AActor{
	GENERATED_BODY()
	
public:	
	AWallObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Procedural Meshes") 
	class UStaticMeshComponent* WallMeshComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
