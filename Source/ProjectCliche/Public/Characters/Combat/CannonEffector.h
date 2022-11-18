// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CannonEffector.generated.h"

UCLASS(Abstract)
class ACannonEffector : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cannon Effector")
	float CannonDamage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cannon Effector")
	float MinCannonRange = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cannon Effector")
	float CurrentCannonRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cannon Effector")
	FTimerHandle ChannelTimerHandler;
	
public:	
	ACannonEffector();

protected:
	virtual void BeginPlay() override;
	
public:
	/**
	 * This will start the cannon logic.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cannon Effector")
	void UseCannon(const float ExtraBoostAmount);

	/**
	 * We essentially need to trace continuously for this to work. So, in blueprints, use cannon will start a timer handler and call this method.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cannon Effector")
	void HandleCannon();
	
	/**
	 * Since the cannon is intended to be a hold channeled attack, we need a way to stop the cannon.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cannon Effector")
	void ReleaseCannon();
	
	/** Get the start and end locations for the trace.*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blast Effector")
	void CalculateTraceStartAndEndPositions(FVector& Start, FVector& End) const;
};
