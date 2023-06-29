// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShootingRangeHUD.generated.h"

class USRInGameMenu;
class USRInventory;
class USRInventoryDisplay;
class USRMainHud;


UCLASS(blueprintable)
class AShootingRangeHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShootingRangeHUD();

	virtual void BeginPlay() override;
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Hud")
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Main Hud")
	USRMainHud* MainHudWidget;

	virtual void InitializeHud();

	USRInventory* Inventory;
	
	class UTexture2D* CrosshairTexure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USRInventoryDisplay> InventoryClass;

	bool bNeedsInventoryInit = true;
	
public:
	void UpdateCroshair();
	virtual void InitializeInventory(USRInventory* PlayerInventory);

	void UpdateTime(float Time, float MaxTime);
	void PrepareTimer(float Time);
	void InteractionKeyOnHud(bool bInteraction);
	void UpdatePointsUI(int32 Points);
	void OnHudSaveGame();
	void EndGameHud();
};
