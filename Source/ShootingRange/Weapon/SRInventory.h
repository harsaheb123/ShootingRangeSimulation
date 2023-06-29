// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRWeapon.h"
#include "SRInventory.generated.h"

class AShootingRangeCharacter;
class ASRWeapon;
class ASRWeaponPickup;

DECLARE_EVENT_OneParam(USRInventory, FSelectedWeaponChanged, FWeaponProperties);
DECLARE_EVENT_OneParam(USRInventory, FWeaponAdded, FWeaponProperties);
DECLARE_EVENT_OneParam(USRInventory, FWeaponRemoved, FWeaponProperties);
DECLARE_EVENT_OneParam(USRInventory, FWeaponUpdate, FWeaponProperties);

USTRUCT(BlueprintType)
struct FWeaponProperties
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(blueprintReadOnly)
	TSubclassOf<ASRWeapon> WeaponClass;

	UPROPERTY(blueprintReadOnly)
	int WeaponPower;

	UPROPERTY(blueprintReadOnly)
	int Ammo;

	UPROPERTY(blueprintReadOnly)
	int MaxAmmo;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTINGRANGE_API USRInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USRInventory();
	
	AShootingRangeCharacter* GetOwningChar();

	virtual void AddDefaultWeapon();
	
	FSelectedWeaponChanged OnSelectedWeaponChanged;
	FWeaponAdded OnWeaponAdded;
	FWeaponRemoved OnWeaponRemoved;
	FWeaponUpdate OnWeaponUpdate;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASRWeaponPickup> DefaultWeaponPickup;

	UPROPERTY(EditAnywhere, blueprintReadWrite)
	TSubclassOf<ASRWeapon> DefaultWeapon;

	void SelectBestWeapon();
	void SelectWeapon(FWeaponProperties Weapon);

	int FindCurrentWeaponIndex() const;

	void SelectNextWeapon();
	void SelectPreviousWeapon();

	void AddWeapon(TSubclassOf<ASRWeapon> Weapon, uint8 WeaponPower, int AmmoCount, int MaxAmmo);

	TSubclassOf<ASRWeapon> GetCurrentWeapon()
	const { return CurrentWeapon; }

	void ChangeAmmo(TSubclassOf<ASRWeapon> Weapon, const int ChangeAmount);

protected:
	TArray<FWeaponProperties> WeaponsArray;
	TSubclassOf<ASRWeapon> CurrentWeapon;
	int CurentWeaponPower = -1;
	AShootingRangeCharacter* MyOwner;

};
