// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShootingRangeCharacter.generated.h"

class AButtonGameplay;
class AShootingRangeGameMode;
class AShootingRangeHUD;
class ASRWeapon;
class USRHudComponent;
class USRInventory;
class USRMainHud;

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class SHOOTINGRANGE_API AShootingRangeCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

public:
	AShootingRangeCharacter();

private:
	virtual void BeginPlay();

private:
	void SaveGame();
	void LoadGame();
	
public:
	int32 BestScore = 0;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

	void SelectNextWeapon();
	void SelectPreviousWeapon();

	//Object interakcji 
	AButtonGameplay* InteractionObject;

	void Interaction();

	bool InteractiveActive = false;

protected:
	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	
	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};

	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);

	TouchData TouchItem;

	ASRWeapon* EquippedWeaponActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	AShootingRangeHUD* ShootingRangeHud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USRInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USRHudComponent* HudComponent;

	virtual void SetInventory(USRInventory* Inv);
	void InitializePlayerHUD();
	virtual void InitializeInventoryHUD();

public:
	void OnHudSaveGame();
	void EndGameHud();
	void UpdateTimer(float TimeCount, float MaxTime);
	void PrepareTimer(float TimeCount);
	void InteractionKeyOnHud(bool bInteraction);
	void UpdateBestScore(int32 ScorePoints);
	void UpdatePointsHud(int32 Points);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() 
	const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() 
	const { return FirstPersonCameraComponent; }

	void EquipWeapon(TSubclassOf<ASRWeapon> Weapon);

	FORCEINLINE ASRWeapon* GetEquippmendWeapon()
	const { return EquippedWeaponActor; };

	FORCEINLINE USRInventory* GetInventory()
	const { return Inventory; }
};

