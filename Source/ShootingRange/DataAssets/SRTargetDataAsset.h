// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SRTargetDataAsset.generated.h"

UCLASS()
class USRTargetDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target Data Asset")
	FText TargetName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target Data Asset")
	FText TargetDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target Data Asset")
	int32 HitPointsValueSmallRing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target Data Asset")
	int32 HitPointsValueNormalRing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target Data Asset")
	int32 HitPointsValueLargeRing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target Data Asset")
	FLinearColor TextCountColor = FLinearColor(1,1,1,1);
};
