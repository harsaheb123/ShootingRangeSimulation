// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRItemBox.generated.h"

class AShootingRangeCharacter;
class USRInventory;
class ASRWeapon;
class UWidgetComponent;
class USRIndicatorBoxUserWidget;

UCLASS()
class SHOOTINGRANGE_API ASRItemBox : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "IndicatorUI")
	UWidgetComponent* IndicatorWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "IndicatorUI")
	USRIndicatorBoxUserWidget* IndicatorWidget;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* ItemBoxMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UAnimMontage* ItemBoxAnimation;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* Root;
	// Sets default values for this actor's properties
	ASRItemBox();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RotationSpeed = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemSettings)
	uint8 Ammunition = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemSettings)
	uint8 WeaponPower = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemSettings")
	TSubclassOf <ASRWeapon> WeaponClass;

};
