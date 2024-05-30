#include "EntranceObject.h"

AEntranceObject::AEntranceObject(): EntranceMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntranceMeshComponent"))),
									EntranceMeshComponentBackward(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntranceMeshComponentBackward"))),
									PillarMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PillarMeshComponent"))) {
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));

	EntranceMeshComponent->SetupAttachment(RootComponent);
	EntranceMeshComponentBackward->SetupAttachment(RootComponent);
	PillarMeshComponent->SetupAttachment(RootComponent);
}

void AEntranceObject::BeginPlay(){
	Super::BeginPlay();
}

void AEntranceObject::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

