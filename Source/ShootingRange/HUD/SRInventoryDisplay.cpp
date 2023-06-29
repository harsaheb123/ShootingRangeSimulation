// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRange/HUD/SRInventoryDisplay.h"
#include "ShootingRange/Weapon/SRInventory.h"

void USRInventoryDisplay::Init(USRInventory* Inventory)
{
	check(Inventory);
	CachedInventory = Inventory;

	CachedInventory->OnSelectedWeaponChanged.AddUObject(this, &USRInventoryDisplay::WeaponSelected);
	CachedInventory->OnWeaponAdded.AddUObject(this, &USRInventoryDisplay::WeaponAdded);
	CachedInventory->OnWeaponRemoved.AddUObject(this, &USRInventoryDisplay::WeaponRemoved);
}

void USRInventoryDisplay::BeginDestroy() 
{
	if (CachedInventory)
	{
		CachedInventory->OnSelectedWeaponChanged.RemoveAll(this);
		CachedInventory->OnWeaponAdded.RemoveAll(this);
		CachedInventory->OnWeaponRemoved.RemoveAll(this);
	}
	Super::BeginDestroy();
}