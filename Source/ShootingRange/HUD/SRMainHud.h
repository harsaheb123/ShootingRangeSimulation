// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShootingRange/Weapon/SRInventory.h"
#include "SRMainHud.generated.h"

class USRInventory;

UCLASS(blueprintable)
class USRMainHud : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	USRInventory* CachedInventory = nullptr;

	UPROPERTY(EditAnywhere, Category = "Hud")
	int32 AmmoCout;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCrosshair();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCountPoints(int32 Points);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimerHUD(float Time, float MaxTime);

	UFUNCTION(BlueprintImplementableEvent)
	void PrepareTimerHUD(float Time);

	UFUNCTION(BlueprintImplementableEvent)
	void SetMaxAmmo(int32 MaxAmmo);

	UFUNCTION(BlueprintImplementableEvent)
	void InteractionKeyOnHud(bool bInteraction);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePointsHud(int32 Points);

	UFUNCTION(BlueprintImplementableEvent)
	void OnHudSaveGame();

	UFUNCTION(BlueprintImplementableEvent)
	void EndGameHud();

	virtual void Init(USRInventory* Inventory);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void WeaponSelected(FWeaponProperties Weapon);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void WeaponAdded(FWeaponProperties Weapon);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void WeaponRemoved(FWeaponProperties Weapon);

	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void WeaponUpdate(FWeaponProperties Weapon);

	virtual void BeginDestroy();
};
