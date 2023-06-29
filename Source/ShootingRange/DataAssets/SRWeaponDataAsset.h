// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "SRWeaponDataAsset.generated.h"

UCLASS(BlueprintType)
class USRWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDataAsset")
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDataAsset")
	UTexture* WeaponImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponDataAsset")
	FLinearColor WeaponColor = FLinearColor(1, 1, 1, 1);
};

USTRUCT(BlueprintType)
struct FWeaponInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponInfo")
	USRWeaponDataAsset* WeaponClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponInfo")
	FText WeaponText;
};
