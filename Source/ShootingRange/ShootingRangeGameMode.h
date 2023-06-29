// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingRangeGameMode.generated.h"

class AShootingRangeCharacter;

UCLASS(minimalapi)
class AShootingRangeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootingRangeGameMode();

protected:

	virtual void BeginPlay() override;
};



