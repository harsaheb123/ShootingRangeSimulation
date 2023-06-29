// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingRange/Target/TargetPointsUserWidget.h"
#include "Components/TextBlock.h"


void UTargetPointsUserWidget::SetUiPoints(int32 Points)
{
	if (PointsTextBlock)
	{
		PointsTextBlock->SetText(FText::AsNumber(Points));
	}
}

void UTargetPointsUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PointsTextBlock)
	{
		PointsTextBlock->SetVisibility(ESlateVisibility::Collapsed);
	}
}