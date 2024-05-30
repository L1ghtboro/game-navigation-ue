#include "WallObject.h"

AWallObject::AWallObject(): WallMeshComponent(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMeshComponent"))) {
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootComponent"));

	WallMeshComponent->SetupAttachment(RootComponent);
}

void AWallObject::BeginPlay(){
	Super::BeginPlay();
	
}

void AWallObject::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

