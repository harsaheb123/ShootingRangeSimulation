// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRange/HUD/SRMainHud.h"
#include "ShootingRange/HUD/SRInventoryDisplay.h"
#include "ShootingRange/Weapon/SRInventory.h"

void USRMainHud::Init(USRInventory* Inventory)
{
	check(Inventory);
	CachedInventory = Inventory;

	Inventory->OnSelectedWeaponChanged.AddUObject(this, &USRMainHud::WeaponSelected);
	Inventory->OnWeaponAdded.AddUObject(this, &USRMainHud::WeaponAdded);
	Inventory->OnWeaponRemoved.AddUObject(this, &USRMainHud::WeaponRemoved);
	Inventory->OnWeaponUpdate.AddUObject(this, &USRMainHud::WeaponUpdate);
}

void USRMainHud::BeginDestroy()
{
	if (CachedInventory)
	{
		CachedInventory->OnSelectedWeaponChanged.RemoveAll(this);
		CachedInventory->OnWeaponAdded.RemoveAll(this);
		CachedInventory->OnWeaponRemoved.RemoveAll(this);
		CachedInventory->OnWeaponUpdate.RemoveAll(this);
	}
	Super::BeginDestroy();
}