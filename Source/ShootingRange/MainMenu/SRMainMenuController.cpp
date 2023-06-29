// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRange/MainMenu/SRMainMenuController.h"
#include "Blueprint/UserWidget.h"

void ASRMainMenuController::BeginPlay()
{
	CreateGameWidget(MainMenuWidget);
}

void ASRMainMenuController::CreateGameWidget(TSubclassOf<UUserWidget> WidgetClassName)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
	if (WidgetClassName != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), WidgetClassName);

		if (CurrentWidget != nullptr)
		{
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
			CurrentWidget->AddToViewport();
		}
	}
}