// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRange/PlayerCharacter/SRStealthCharacter.h"
#include "Components/InputComponent.h"

void ASRStealthCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Bind stelth events
	PlayerInputComponent->BindAction("Stealth", IE_Pressed, this, &ASRStealthCharacter::Stealth);
	PlayerInputComponent->BindAction("Stealth", IE_Released, this, &ASRStealthCharacter::UnStealth);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASRStealthCharacter::AddControllerPitchInput(float Val)
{
	const float fScale = bIsStealthed ? StealthPitchYawScale : 1.0f;
	Super::AddControllerPitchInput(Val * fScale);
}

void ASRStealthCharacter::AddControllerYawInput(float Val)
{
	const float fScale = bIsStealthed ? StealthPitchYawScale : 1.0f;
	Super::AddControllerYawInput(Val * fScale);
}

void ASRStealthCharacter::Stealth()
{
	bIsStealthed = true;
	Super::Crouch();
}

void ASRStealthCharacter::UnStealth()
{
	bIsStealthed = false;
	Super::UnCrouch();
}