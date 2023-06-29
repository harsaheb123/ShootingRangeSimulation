// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetPointsUserWidget.generated.h"

UCLASS()
class UTargetPointsUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "TargetWidget")
	class UTextBlock* PointsTextBlock;
	
	UPROPERTY(EditAnywhere, Category = "TargetWidget")
	UWidgetAnimation* AddPointsAnimation;

	void SetUiPoints(int32 Points);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHitTargetAnimation();

private:
	virtual void NativeConstruct() override;

};
