// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonGameplay.generated.h"

class AShootingRangeCharacter;
class USRInteractPromptWidget;
class UWidgetComponent;
class ASRTargetActor; 

UCLASS()
class SHOOTINGRANGE_API AButtonGameplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonGameplay();

private:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Target")
	UWidgetComponent* InteractPromptWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Target")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Target")
	USRInteractPromptWidget* InteractPromptUIWidget;

	UFUNCTION(BlueprintCallable)
	void SetInteractPromptUI(bool bInteract);

	UFUNCTION(BlueprintCallable)
	void UpdatePoints(int32 Points);

	UFUNCTION(BlueprintCallable)
	void UpdatePointsUI(int32 Count);

	int32 GamePoints;

protected:
	void RestartPoints(int32 Count);
	// Called when the game starts or when spawned

public:	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Timer")
	float PrepareCountTime = 4.0f;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float StartPrepareTimer = PrepareCountTime;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float Second = 30.0f;

	UPROPERTY(EditAnywhere, Category = "Timer")
	float StarterTime = Second;

public:
	void StartGame();
	void StopGame();

	void StartInteraction();
	void CountDown();
	void PrepareCountTimer();

	FTimerHandle TimerHandle;

	bool bButtonFlag = true;
	bool bActiveTimer = true;

	AButtonGameplay* ButtonActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	AShootingRangeCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Target")
	ASRTargetActor* CurrentTarget;

	UPROPERTY(EditAnywhere, Category = "Target")
	TArray<ASRTargetActor*> ShootingTargetsArray;
};
