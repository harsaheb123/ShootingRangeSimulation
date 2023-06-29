// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SRMainMenuController.generated.h"

/**
 * 
 */
UCLASS()
class ASRMainMenuController : public APlayerController
{
	GENERATED_BODY()

private:
	UFUNCTION(BlueprintCallable, Category = "Main Menu")
	void CreateGameWidget(TSubclassOf<UUserWidget> WidgetClassName);


protected:

	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main Menu")
	TSubclassOf<UUserWidget> MainMenuWidget;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
