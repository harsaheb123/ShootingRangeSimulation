#include "ShootingRange/Weapon/SRWeapon.h"
#include "ShootingRange/Weapon/SRInventory.h"
#include "ShootingRange/ShootingRangeProjectile.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

ASRWeapon::ASRWeapon()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetOnlyOwnerSee(true);
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;
	WeaponMesh->SetupAttachment(RootComponent);

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(WeaponMesh);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASRWeapon::Fire(FRotator ControlRotation, UAnimInstance* AnimInst, USRInventory* Inventory)
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		
		if (World != nullptr)
		{
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + ControlRotation.RotateVector(GunOffset);

			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Instigator = Cast<APawn>(GetOwner());
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AShootingRangeProjectile>(ProjectileClass, SpawnLocation, ControlRotation, ActorSpawnParameters);
		}
	}
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (AnimInst != nullptr)
	{
		if (AnimInst != nullptr)
		{
			AnimInst->Montage_Play(FireAnimation, 1.0f);
		}
	}

	Inventory->ChangeAmmo(GetClass(), -1);
};