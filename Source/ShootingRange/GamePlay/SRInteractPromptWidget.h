// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SRInteractPromptWidget.generated.h"
//#include "Components/Image.h"
/**
 * 
 */
UCLASS()
class SHOOTINGRANGE_API USRInteractPromptWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ActivePrompt(bool bIsActive);
};
