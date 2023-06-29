// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetComponent.h"
#include "ShootingRange/Gameplay/ButtonGameplay.h"
#include "ShootingRange/Target/SRTargetActor.h"
#include "ShootingRange/Gameplay/SRInteractPromptWidget.h"
#include "ShootingRange/ShootingRangeCharacter.h"

// Sets default values
AButtonGameplay::AButtonGameplay()
{
	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);
	InteractPromptWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("WidgetUI")));
	InteractPromptWidgetComponent->AttachTo(RootComponent);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AButtonGameplay::BeginPlay()
{
	Super::BeginPlay();

	GamePoints = 0;
}

void AButtonGameplay::SetInteractPromptUI(bool bInteract)
{
	if (InteractPromptWidgetComponent)
	{
		if (InteractPromptUIWidget == NULL)
		{
			InteractPromptUIWidget = Cast<USRInteractPromptWidget>(InteractPromptWidgetComponent->GetWidget());
		}
		if(InteractPromptUIWidget)
		{
			InteractPromptUIWidget->ActivePrompt(bInteract);
		}
	}
}

// Called when the game starts or when spawned
void AButtonGameplay::UpdatePoints(int32 Points)
{
	GamePoints = GamePoints + Points;
	UpdatePointsUI(GamePoints);
}

void AButtonGameplay::UpdatePointsUI(int32 Points)
{
		if (PlayerCharacter)
		{
			PlayerCharacter->UpdatePointsHud(Points);
		}
}

void AButtonGameplay::NotifyActorBeginOverlap(AActor* OtherActor)
{
	PlayerCharacter = Cast<AShootingRangeCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->InteractionKeyOnHud(true);
		SetInteractPromptUI(true);
		PlayerCharacter->InteractiveActive = true;
		PlayerCharacter->InteractionObject = this;
	}
}

void AButtonGameplay::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->InteractionKeyOnHud(false);
		SetInteractPromptUI(false);
		PlayerCharacter->InteractiveActive = false;
		PlayerCharacter->InteractionObject = nullptr;
	}
}

void AButtonGameplay::StartGame()
{
	GamePoints = 0;
	UpdatePointsUI(GamePoints);

	for (auto TargetNumber = 0; TargetNumber < ShootingTargetsArray.Num(); TargetNumber++)
	{
		CurrentTarget = Cast<ASRTargetActor>(ShootingTargetsArray[TargetNumber]);
		if (CurrentTarget != NULL)
			{
				CurrentTarget->bTargetActive = true;
				CurrentTarget->StartMoveTarget();
				PlayerCharacter->EndGameHud();
			}
	}
}

void AButtonGameplay::StopGame()
{
	for (auto TargetNumber = 0; TargetNumber < ShootingTargetsArray.Num(); TargetNumber++)
	{
		CurrentTarget = Cast<ASRTargetActor>(ShootingTargetsArray[TargetNumber]);
		if (CurrentTarget != NULL)
			{
				CurrentTarget->bTargetActive = false;
				CurrentTarget->StopMoveTarget();
			}
	}
	if (PlayerCharacter)
	{
		PlayerCharacter->UpdateBestScore(GamePoints);
	}
}

void AButtonGameplay::StartInteraction()
{
	if (bActiveTimer)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AButtonGameplay::PrepareCountTimer, 1.f, true, 0.0);
	}
	else
	{
		if (bButtonFlag)
		{
			bButtonFlag = false;
			bActiveTimer = true;
			StartGame();
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AButtonGameplay::CountDown, 1.f, true, 0.0);
		}
		else
		{
			return;
		}
	}
}

void AButtonGameplay::CountDown()
{
	if (Second > 0)
	{
		Second = Second - 1;
		PlayerCharacter->UpdateTimer(Second, StarterTime);
	}
	else
	{
		bButtonFlag = true;
		Second = StarterTime;
		PlayerCharacter->UpdateTimer(StarterTime, StarterTime);
		GetWorldTimerManager().ClearTimer(TimerHandle);
		StopGame();
	}
}

void AButtonGameplay::PrepareCountTimer()
{
	if (PrepareCountTime > 0)
	{
		PrepareCountTime = PrepareCountTime - 1;
		PlayerCharacter->PrepareTimer(PrepareCountTime);
	}
	else
	{
		bActiveTimer = false;
		PrepareCountTime = StartPrepareTimer;
		GetWorldTimerManager().ClearTimer(TimerHandle);
		StartInteraction();
	}
}
