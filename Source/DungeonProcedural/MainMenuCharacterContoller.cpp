
#include "MainMenuCharacterContoller.h"

void AMainMenuCharacterContoller::BeginPlay() {
	Super::BeginPlay();

	bShowMouseCursor = true;

	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeData);
}