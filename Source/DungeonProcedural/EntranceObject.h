#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntranceObject.generated.h"

UCLASS() class DUNGEONPROCEDURAL_API AEntranceObject : public AActor{
	GENERATED_BODY()
	
public:	
	AEntranceObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* EntranceMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* EntranceMeshComponentBackward;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* PillarMeshComponent;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
