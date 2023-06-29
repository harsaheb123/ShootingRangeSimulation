// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SRTimerWidget.generated.h"

UENUM(BlueprintType)
enum class USRTimeState : uint8
{
	LowTime,
	MidiumTime,
	NormalTime,
};

UCLASS()
class SHOOTINGRANGE_API USRTimerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Target")
	float StateLowTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Target")
	float StateMidiuumTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Target")
	float StateNormalTime = 0.0f;

	UFUNCTION(BlueprintCallable)
	void UpdateTimer(float Time);
};
