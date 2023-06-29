// Fill out your copyright notice in the Description page of Project Settings.
#include "ShootingRange/Target/SRTargetActor.h"
#include "Components/WidgetComponent.h"
#include "ShootingRange/Target/TargetPointsUserWidget.h"
#include "ShootingRange/GamePlay/ButtonGameplay.h"

// Sets default values
ASRTargetActor::ASRTargetActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);
	PointsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("WidgetUI")));
	PointsWidgetComponent->AttachTo(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASRTargetActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASRTargetActor::SetPointsUI()
{
	if (PointsWidgetComponent)
	{
		if (PointsUiWidget == NULL)
		{
			PointsUiWidget = Cast<UTargetPointsUserWidget>(PointsWidgetComponent->GetWidget());
		}
		if (PointsUiWidget && ButtonClass)
		{
			PointsUiWidget->SetUiPoints(PointsValue);
			PointsUiWidget->PlayHitTargetAnimation();
			ButtonClass->UpdatePoints(PointsValue);
		}
	}
}

void ASRTargetActor::StartMoveTarget()
{
	if (bTargetActive)
	{
		ActualyPosition = DefaultPosition;
		SetActorLocation(ActualyPosition);
		GetWorldTimerManager().ClearTimer(TimerHandle);
		bMoveTargetActive = true;
	}
}

void ASRTargetActor::StopMoveTarget()
{
	ActualyPosition = OutOfSceneLocation;
	SetActorLocation(ActualyPosition);

	bMoveTargetActive = false;
}

void ASRTargetActor::HitTargetT()
{
	UpdatePoints();
	SetPointsUI();
	StopMoveTarget();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASRTargetActor::StartMoveTarget, 1.f, true, TimeToMove);
}

void ASRTargetActor::UpdatePoints()
{
	if (ButtonClass == NULL)
	{
		ButtonClass = Cast<AButtonGameplay>(ButtonClass);
	}
	if (ButtonClass)
	{
		ButtonClass->UpdatePoints(PointsValue);
	}
}
// Called when the game starts or when spawned

void ASRTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bShoutMoveObject)
	{
		if (bMoveTargetActive)
		{
			FVector Pos = GetActorLocation();
			Pos.Y = FMath::Sin(GetGameTimeSinceCreation() * Speed) * Range;
			SetActorLocation(Pos);
		}
	}

}
