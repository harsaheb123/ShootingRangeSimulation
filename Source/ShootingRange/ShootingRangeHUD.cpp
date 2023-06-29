// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingRangeHUD.h"
#include "ShootingRange/Weapon/SRInventory.h"
#include "ShootingRange/HUD/SRInventoryDisplay.h"
#include "ShootingRange/HUD/SRMainHud.h"

#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AShootingRangeHUD::AShootingRangeHUD()
{
}

void AShootingRangeHUD::BeginPlay()
{
}

void AShootingRangeHUD::DrawHUD()
{
	if (bNeedsInventoryInit)
	{
		bNeedsInventoryInit = false;

		InitializeHud();
	}

	Super::DrawHUD();
}

void AShootingRangeHUD::InitializeHud()
{
	if (IsValid(WidgetClass))
	{
		if (MainHudWidget == NULL)
		{
			MainHudWidget = Cast <USRMainHud>(CreateWidget(GetWorld(), WidgetClass));
		}

		if (MainHudWidget != nullptr)
		{
			MainHudWidget->AddToViewport();
		}
	}
}

void AShootingRangeHUD::InitializeInventory(USRInventory* PlayerInventory)
{
	if (MainHudWidget == NULL)
	{
		MainHudWidget = Cast <USRMainHud>(CreateWidget(GetWorld(), WidgetClass));
	}

	Inventory = PlayerInventory;
	if (MainHudWidget != nullptr)
	{
		MainHudWidget->Init(Inventory);
	}
}

void AShootingRangeHUD::UpdateCroshair()
{
	if (MainHudWidget)
	{
		MainHudWidget->UpdateCrosshair();
	}
}

void AShootingRangeHUD::UpdateTime(float Time, float MaxTime)
{
	if (MainHudWidget)
	{
		MainHudWidget->UpdateTimerHUD(Time, MaxTime);
	}
}

void AShootingRangeHUD::PrepareTimer(float Time)
{
	if (MainHudWidget)
	{
		MainHudWidget->PrepareTimerHUD(Time);
	}
}

void AShootingRangeHUD::InteractionKeyOnHud(bool bInteraction) 
{
	//if (MainHudWidget)
	//{
	//	MainHudWidget->InteractionKeyOnHud(bInteraction);
	//}
}

void AShootingRangeHUD::UpdatePointsUI(int32 Points)
{
	if (MainHudWidget)
	{
		MainHudWidget->UpdatePointsHud(Points);
	}
}

void AShootingRangeHUD::OnHudSaveGame()
{
	if (MainHudWidget)
	{
		MainHudWidget->OnHudSaveGame();
	}
}

void AShootingRangeHUD::EndGameHud()
{
	if (MainHudWidget)
	{
		MainHudWidget->EndGameHud();
	}
}



