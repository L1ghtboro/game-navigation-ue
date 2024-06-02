#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuSetupUI.generated.h"

UCLASS()
class DUNGEONPROCEDURAL_API UMainMenuSetupUI : public UUserWidget {
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTestMapStatic;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonTestMap;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonClosedCityMap;

	UPROPERTY(meta = (BindWidget))
	class UButton* ButtonQuit;

	UFUNCTION()
	void OnTestMapStaticClicked();

	UFUNCTION()
	void OnTestMapClicked();

	UFUNCTION()
	void OnClosedCityMapClicked();

	UFUNCTION()
	void OnQuitClicked();
};
