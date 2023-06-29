// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingRange/Weapon/SRInventory.h"
#include "ShootingRange/ShootingRangeCharacter.h"
#include "ShootingRange/Weapon/SRWeaponPickup.h"

#define UNLIMITED_AMMO -1

// Sets default values for this component's properties
USRInventory::USRInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AShootingRangeCharacter* USRInventory::GetOwningChar() 
{
	if(!MyOwner) 
	{
		MyOwner = CastChecked<AShootingRangeCharacter>(GetOwner());
	}
	check(MyOwner);
	return MyOwner;
}

void USRInventory::AddDefaultWeapon()
{
	if (DefaultWeaponPickup != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn a pickup and immediately add it to our player
		ASRWeaponPickup* defaultPickup = GetWorld()->SpawnActor<ASRWeaponPickup>(DefaultWeaponPickup, FVector(0.0f), FRotator(0.0f), ActorSpawnParams);
		defaultPickup->HavePlayerPickup(GetOwningChar());
	}
}

void USRInventory::SelectBestWeapon()
{
	int highestWeaponPower = CurentWeaponPower;
	FWeaponProperties bestWeapon;

	OnSelectedWeaponChanged.Broadcast(bestWeapon);

	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		const FWeaponProperties& currentProps = *WeaponIt;
		if(currentProps.Ammo == 0) 
		{
			continue;
		}
		if (currentProps.WeaponPower > highestWeaponPower)
		{
			highestWeaponPower = currentProps.WeaponPower;
			CurentWeaponPower = highestWeaponPower;
			bestWeapon = currentProps;
		}
	}

	if (bestWeapon.WeaponClass != nullptr)
	{
		SelectWeapon(bestWeapon);
	}
}

void USRInventory::SelectWeapon(FWeaponProperties Weapon)
{
	OnSelectedWeaponChanged.Broadcast(Weapon);

	GetOwningChar()->EquipWeapon(Weapon.WeaponClass);
	CurrentWeapon = Weapon.WeaponClass;
}

int USRInventory::FindCurrentWeaponIndex() const
{
	int currentIdex = 0;

	for (auto WeaponIt = WeaponsArray.CreateConstIterator(); WeaponIt; ++WeaponIt, ++currentIdex)
	{
		const FWeaponProperties& currentProps = *WeaponIt;

		if (currentProps.WeaponClass == CurrentWeapon)
		{
			break;
		}
	}
	checkSlow(curentIndex < WeaponsArray.Num());
	return currentIdex;
}

void USRInventory::SelectNextWeapon()
{
	if (WeaponsArray.Num() != NULL)
	{
		int currentIndex = FindCurrentWeaponIndex();

		if (currentIndex == WeaponsArray.Num() - 1)
		{
			SelectWeapon(WeaponsArray[0]);
		}
		else
		{
			SelectWeapon(WeaponsArray[currentIndex + 1]);
		}
	}
}

void USRInventory::SelectPreviousWeapon()
{
	if (WeaponsArray.Num() != NULL)
	{
		int currentIndex = FindCurrentWeaponIndex();

		if (currentIndex > 0)
		{
			SelectWeapon(WeaponsArray[currentIndex - 1]);
		}
		else
		{
			SelectWeapon(WeaponsArray[WeaponsArray.Num() - 1]);
		}
	}
}

void USRInventory::AddWeapon(TSubclassOf<ASRWeapon> Weapon, uint8 WeaponPower, int AmmoCount, int MaxAmmo)
{
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponProperties& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon )
		{
			checkSlow(AmmoCount >= 0);
			currentProps.Ammo += AmmoCount;
			return;
		}
	}
		FWeaponProperties WeaponProps;
		WeaponProps.WeaponClass = Weapon;
		WeaponProps.WeaponPower = WeaponPower;
		WeaponProps.Ammo = AmmoCount;
		WeaponProps.MaxAmmo = MaxAmmo;

		WeaponsArray.Add(WeaponProps);
		OnWeaponAdded.Broadcast(WeaponProps);
}

void USRInventory::ChangeAmmo(TSubclassOf<ASRWeapon> Weapon, const int ChangeAmount) 
{
	OnWeaponUpdate.RemoveAll(this);

	for (int WeaponIt = 0; WeaponIt < WeaponsArray.Num(); ++WeaponIt)
	{
		FWeaponProperties& curentProps = WeaponsArray[WeaponIt];
		if (curentProps.WeaponClass == Weapon)
		{
			if (curentProps.WeaponPower == UNLIMITED_AMMO)
			{
				return;
			}
			curentProps.Ammo = FMath::Clamp(curentProps.Ammo + ChangeAmount, 0, 999);
			OnWeaponUpdate.Broadcast(curentProps);

			if (curentProps.Ammo == 0)
			{
				CurentWeaponPower = -1;
				OnWeaponRemoved.Broadcast(curentProps); 
				WeaponsArray.RemoveAt(WeaponIt);
				SelectBestWeapon();
			}
			return;
		}
	}
}

