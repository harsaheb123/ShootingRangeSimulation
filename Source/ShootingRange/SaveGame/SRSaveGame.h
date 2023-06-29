// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SRSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGRANGE_API USRSaveGame : public USaveGame
{
	GENERATED_BODY()

	USRSaveGame();

public:
	UPROPERTY(EditAnywhere)
	int32 ShootingPoints;
};
