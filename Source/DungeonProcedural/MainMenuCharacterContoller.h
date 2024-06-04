#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuCharacterContoller.generated.h"

UCLASS() class DUNGEONPROCEDURAL_API AMainMenuCharacterContoller : public APlayerController {
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
