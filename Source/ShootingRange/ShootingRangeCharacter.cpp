// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingRangeCharacter.h"
#include "ShootingRange/HUD/SRMainHud.h"
#include "XRMotionControllerBase.h"
#include "ShootingRange/Weapon/SRInventory.h"
#include "ShootingRange/Weapon/SRWeapon.h"
#include "GameFramework/GameModeBase.h"
#include "ShootingRange/ShootingRangeHUD.h"
#include "ShootingRange/Gameplay/ButtonGameplay.h"
#include "ShootingRange/ShootingRangeGameMode.h"
#include "ShootingRange/SaveGame/SRSaveGame.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

#include "ShootingRange/HUD/SRHudComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AShootingRangeCharacter::AShootingRangeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.0f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));

	Inventory = CreateDefaultSubobject<USRInventory>(TEXT("Inventory"));
	HudComponent = CreateDefaultSubobject<USRHudComponent>(TEXT("HudComponent"));
}

void AShootingRangeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (Inventory != nullptr)
	{
		Inventory->SelectBestWeapon();
		Inventory->AddDefaultWeapon();
	}
	InitializeInventoryHUD();
	InitializePlayerHUD();
}

void AShootingRangeCharacter::SaveGame()
{
	//Create an instatnce of our save game class
	USRSaveGame* SaveGameInstance = Cast<USRSaveGame>(UGameplayStatics::CreateSaveGameObject(USRSaveGame::StaticClass()));
	//Set the save game instance
	SaveGameInstance->ShootingPoints = BestScore;
	//Save game instance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("MyGameSlot"), 0);
	ShootingRangeHud->OnHudSaveGame();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("SaveGame")); /*DebugMessage*/
}

void AShootingRangeCharacter::LoadGame()
{
	//Create an instatnce of our save game class
	USRSaveGame* SaveGameInstance = Cast<USRSaveGame>(UGameplayStatics::CreateSaveGameObject(USRSaveGame::StaticClass()));
	//load the save game instance
	SaveGameInstance = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot("MyGameSlot", 0));
	//Set the players position from the saved game file
	this->UpdatePointsHud(SaveGameInstance->ShootingPoints);
	ShootingRangeHud->OnHudSaveGame();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("LoadGame")); /*DebugMessage*/
}

void AShootingRangeCharacter::InitializePlayerHUD()
{
	APlayerController* player = Cast<APlayerController>(GetController());
	if (player != nullptr)
	{
		ShootingRangeHud = Cast<AShootingRangeHUD>(player->GetHUD());
	}
}

void AShootingRangeCharacter::InitializeInventoryHUD()
{
	APlayerController* player = Cast<APlayerController>(GetController());
	if (player != nullptr)
	{
		AShootingRangeHUD* HUD = Cast<AShootingRangeHUD>(player->GetHUD());

		if (HUD != nullptr)
		{
			HUD->InitializeInventory(Inventory);
		}
	}
}

void AShootingRangeCharacter::EndGameHud()
{
	ShootingRangeHud->EndGameHud();
}

void AShootingRangeCharacter::OnHudSaveGame()
{
	ShootingRangeHud->OnHudSaveGame();
}

void AShootingRangeCharacter::SetInventory(USRInventory* Inv)
{
	Inventory = Inv;
	InitializeInventoryHUD();
}

void AShootingRangeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShootingRangeCharacter::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AShootingRangeCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AShootingRangeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShootingRangeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShootingRangeCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShootingRangeCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("InventoryUp", IE_Pressed, this, &AShootingRangeCharacter::SelectNextWeapon);
	PlayerInputComponent->BindAction("InventoryDown", IE_Pressed, this, &AShootingRangeCharacter::SelectPreviousWeapon);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AShootingRangeCharacter::Interaction);

	PlayerInputComponent->BindAction("SaveGame", IE_Pressed, this, &AShootingRangeCharacter::SaveGame);
	PlayerInputComponent->BindAction("LoadGame", IE_Pressed, this, &AShootingRangeCharacter::LoadGame);
	
}

void AShootingRangeCharacter::SelectNextWeapon()
{
	if (Inventory != nullptr)
	{
		Inventory->SelectNextWeapon();
	}
}

void AShootingRangeCharacter::SelectPreviousWeapon()
{
	if (Inventory != nullptr)
	{
		Inventory->SelectPreviousWeapon();
	}
}

void AShootingRangeCharacter::Interaction()
{
	AButtonGameplay* ObjectButton = Cast<AButtonGameplay>(InteractionObject);

	if (ObjectButton)
	{
		ObjectButton->StartInteraction();
	}
}

void AShootingRangeCharacter::UpdateTimer(float Time, float MaxTime)
{
	if (ShootingRangeHud != nullptr)
	{
		ShootingRangeHud->UpdateTime(Time, MaxTime);
	}
}

void AShootingRangeCharacter::PrepareTimer(float Time)
{
	if (ShootingRangeHud != nullptr)
	{
		ShootingRangeHud->PrepareTimer(Time);
	}
}

void AShootingRangeCharacter::InteractionKeyOnHud(bool bInteraction)
{
	ShootingRangeHud->InteractionKeyOnHud(bInteraction);
}

void AShootingRangeCharacter::UpdateBestScore(int32 ScorePoints)
{
	if (ScorePoints > BestScore)
	{
		BestScore = ScorePoints;
		SaveGame();
	}
	UpdatePointsHud(BestScore);
}

void AShootingRangeCharacter::UpdatePointsHud(int32 Points)
{
	if (ShootingRangeHud != nullptr)
	{
		ShootingRangeHud->UpdatePointsUI(Points);
	}
}

void AShootingRangeCharacter::OnFire()
{
	if (GetEquippmendWeapon() != nullptr)
	{
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		GetEquippmendWeapon()->Fire(GetControlRotation(), AnimInstance, Inventory);
		if (ShootingRangeHud)
		{
			ShootingRangeHud->UpdateCroshair();
		}
	}
}

void AShootingRangeCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AShootingRangeCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void AShootingRangeCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void AShootingRangeCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AShootingRangeCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AShootingRangeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShootingRangeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool AShootingRangeCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AShootingRangeCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AShootingRangeCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AShootingRangeCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}

void AShootingRangeCharacter::EquipWeapon(TSubclassOf<ASRWeapon> Weapon)
{
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}

	if (EquippedWeaponActor != nullptr)
	{
		if (EquippedWeaponActor->IsA(Weapon))
		{
			return;
		}

		World->DestroyActor(EquippedWeaponActor);
	}
	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParams.Owner = this;

	EquippedWeaponActor = Cast<ASRWeapon>(World->SpawnActor(Weapon, &SpawnLocation, &SpawnRotation, ActorSpawnParams));
	if (EquippedWeaponActor != nullptr)
	{
		EquippedWeaponActor->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true)), TEXT("GripPoint");
	}
}
