// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootingRange/Weapon/SRInventory.h"
#include "SRInventoryDisplay.generated.h"


class USRInventory;

UCLASS()
class SHOOTINGRANGE_API USRInventoryDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Init(USRInventory* Inventory);
	virtual void BeginDestroy();

	UPROPERTY()
	USRInventory* CachedInventory = nullptr;
	
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void WeaponSelected(FWeaponProperties Weapon);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void WeaponAdded(FWeaponProperties Weapon);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void WeaponRemoved(FWeaponProperties Weapon);
};
