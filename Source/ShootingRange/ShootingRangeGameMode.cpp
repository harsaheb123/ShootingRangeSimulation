#include "ShootingRangeGameMode.h"
#include "ShootingRangeHUD.h"
#include "ShootingRangeCharacter.h"
#include "ShootingRange/HUD/SRMainHud.h"
#include "ShootingRange/ShootingRangeCharacter.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AShootingRangeGameMode::AShootingRangeGameMode()
	: Super()
{
	// use our custom HUD class
	HUDClass = AShootingRangeHUD::StaticClass();
}

void AShootingRangeGameMode::BeginPlay()
{
}
