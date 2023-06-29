#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRWeapon.generated.h"
//#include "ShootingRange/ShootingRangeProjectile.h" todo: move to.cpp
class AShootingRangeProjectile;
class USRInventory;

class UAnimMontage;
class USceneComponent;
class USkeletalMeshComponent;
class USoundBase;

UCLASS()
class SHOOTINGRANGE_API ASRWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASRWeapon();
	
public:	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset = FVector(100.0f, 0.0f, 10.0f);

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AShootingRangeProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* WeaponMesh;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;

public:
	void Fire(FRotator ControlRotation, UAnimInstance* AnimInst, USRInventory* Inventory);

};
