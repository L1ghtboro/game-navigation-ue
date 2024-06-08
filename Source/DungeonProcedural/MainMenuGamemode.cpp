
#include "MainMenuGamemode.h"
#include "MainMenuCharacterContoller.h"

AMainMenuGamemode::AMainMenuGamemode() {
	PlayerControllerClass = AMainMenuCharacterContoller::StaticClass();
}