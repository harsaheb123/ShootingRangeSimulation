#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRWeaponPickup.generated.h"

class USRInventory;
class AShootingRangeCharacter;
class ASRWeapon;

UCLASS()
class SHOOTINGRANGE_API ASRWeaponPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASRWeaponPickup();

protected:
	// Called when the game starts or when spawnedStartGameWidget
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HavePlayerPickup(AShootingRangeCharacter* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf <ASRWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RotationSpeed = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 Ammunition = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 WeaponPower = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 MaxAmmunition  = 10;
	
};
