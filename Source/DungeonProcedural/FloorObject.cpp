#include "FloorObject.h"

AFloorObject::AFloorObject() : FloorMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshComponent"))) {
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));

	FloorMeshComponent->SetupAttachment(RootComponent);
}

void AFloorObject::BeginPlay(){
	Super::BeginPlay();
	
}

void AFloorObject::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

