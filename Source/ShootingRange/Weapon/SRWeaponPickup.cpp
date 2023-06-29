#include "ShootingRange/ShootingRangeCharacter.h"
#include "ShootingRange/Weapon/SRInventory.h"
#include "ShootingRange/Weapon/SRWeapon.h"
#include "ShootingRange/Weapon/SRWeaponPickup.h"

// Sets default values
ASRWeaponPickup::ASRWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASRWeaponPickup::BeginPlay()
{
	Super::BeginPlay();	
}

void ASRWeaponPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AShootingRangeCharacter* player = Cast<AShootingRangeCharacter>(OtherActor);

	if (player == nullptr)
	{
		return;
	}

	HavePlayerPickup(player);
}

// Called every frame
void ASRWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotationAmount(0.0f, DeltaTime * RotationSpeed, 0.0f);

	AddActorLocalRotation(rotationAmount);
}

void ASRWeaponPickup::HavePlayerPickup(AShootingRangeCharacter* Player)
{
	USRInventory* Inventory = Player->GetInventory();
	Inventory->AddWeapon(WeaponClass, WeaponPower, Ammunition, MaxAmmunition);
	Inventory->SelectBestWeapon();
	// ToDo: Add weapon object to Inventory
	Destroy();
}

