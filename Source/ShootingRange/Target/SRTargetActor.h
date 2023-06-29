// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRTargetActor.generated.h"

class UTargetPointsUserWidget;
class UWidgetComponent;
class AButtonGameplay;

UCLASS()
class ASRTargetActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASRTargetActor();

private:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Target")
	int32 PointsValue = 500;

	UPROPERTY(EditAnywhere, Category = "Target")
	float TimeToMove = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Target")
	UWidgetComponent* PointsWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Target")
	bool bShoutMoveObject;
	
	UPROPERTY(EditAnywhere, Category = "Target")
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, Category = "Target")
	UTargetPointsUserWidget* PointsUiWidget;

	UPROPERTY(EditAnywhere, Category = "Target")
	AButtonGameplay* ButtonClass;

	ASRTargetActor* TargetClass;

	UFUNCTION(BlueprintCallable)
	void SetPointsUI();

	void UpdatePoints();

	UFUNCTION(BlueprintCallable)
	void StartMoveTarget();

	UFUNCTION(BlueprintCallable)
	void StopMoveTarget();

	UFUNCTION(BlueprintCallable)
	void HitTargetT();

	bool bTargetActive;
	bool bMoveTargetActive;
protected:
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Target Move")
	FVector DefaultPosition;

	UPROPERTY(EditAnyWhere, Category = "Target Move")
	FVector OutOfSceneLocation;

	FVector ActualyPosition;

	UPROPERTY(EditAnywhere, Category = "Target Move")
	float Range = 0.0f;

	UPROPERTY(EditAnyWhere, Category = "Target Move")
	float Speed = 0.0f;

	virtual void Tick(float DeltaTime) override;
	// Called when the game starts or when spawned

};

