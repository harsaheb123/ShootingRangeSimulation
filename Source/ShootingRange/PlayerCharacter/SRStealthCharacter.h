// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingRange/ShootingRangeCharacter.h"
#include "SRStealthCharacter.generated.h"

class UImputControler;

UCLASS()
class SHOOTINGRANGE_API ASRStealthCharacter : public AShootingRangeCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float StealthPitchYawScale = 0.2f;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

	void Stealth();
	void UnStealth();

protected:
	bool bIsStealthed = false;
};
