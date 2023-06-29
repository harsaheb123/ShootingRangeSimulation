// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRange/Items/SRItemBox.h"
#include "ShootingRange/Weapon/SRInventory.h"
#include "ShootingRange/ShootingRangeCharacter.h"
#include "ShootingRange/Weapon/SRWeapon.h"
#include "ShootingRange/Items/SRIndicatorBoxUserWidget.h"

// Sets default values
ASRItemBox::ASRItemBox()
{
	/*Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);
	IndicatorWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("WidgetUI")));*/
	//IndicatorWidgetComponent->AttachTo(RootComponent);
	// 
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASRItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}
void ASRItemBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AShootingRangeCharacter* Player = Cast<AShootingRangeCharacter>(OtherActor);
	
	if (Player == nullptr)
	{
		return;
	}
	USRInventory* Inventory = Player->GetInventory();

	//TODO:UPDATE TO NEW REFERENCES AddWeapons(TFWeaponProperties)
	// 
	//Inventory->AddWeapon(PropertWeaponClass, Ammunition, WeaponPower);
	//Inventory->SelectBestWeapon();
	 Destroy();
}
