// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRHudComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTINGRANGE_API USRHudComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USRHudComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	//void OnHudSaveGame();
	//void EndGameHud();
	//void UpdateTimer(float TimeCount, float MaxTime);
	//void PrepareTimer(float TimeCount);
	//void InteractionKeyOnHud(bool bInteraction);


	//void UpdateBestScore(int32 ScorePoints);
	//void UpdatePointsHud(int32 Points);
};
