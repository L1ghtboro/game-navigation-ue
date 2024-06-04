#include "MainMenuSetupUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuSetupUI::NativeConstruct() {
	Super::NativeConstruct();

	// Bind button click events
	if (ButtonTestMapStatic) {
		ButtonTestMapStatic->OnClicked.AddDynamic(this, &UMainMenuSetupUI::OnTestMapStaticClicked);
	}

	if (ButtonTestMap) {
		ButtonTestMap->OnClicked.AddDynamic(this, &UMainMenuSetupUI::OnTestMapClicked);
	}

	if (ButtonClosedCityMap) {
		ButtonClosedCityMap->OnClicked.AddDynamic(this, &UMainMenuSetupUI::OnClosedCityMapClicked);
	}

	if (ButtonQuit) {
		ButtonQuit->OnClicked.AddDynamic(this, &UMainMenuSetupUI::OnQuitClicked);
	}
}

void UMainMenuSetupUI::OnTestMapStaticClicked() {
	UGameplayStatics::OpenLevel(this, FName("TestStaticMap"));
}

void UMainMenuSetupUI::OnTestMapClicked() {
	UGameplayStatics::OpenLevel(this, FName("TestMap"));
}

void UMainMenuSetupUI::OnClosedCityMapClicked() {
	UGameplayStatics::OpenLevel(this, FName("ClosedCityMap"));
}

void UMainMenuSetupUI::OnQuitClicked() {
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
