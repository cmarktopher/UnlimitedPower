// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlastEffector.generated.h"

UCLASS(Abstract)
class ABlastEffector : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	float BlastDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	float BoostDampenerMultiplier = 0.2; // This will likely be changed to something else once I figure out a better way to balance the boost system.
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	float BlastDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	float BlastRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	float MaxPushbackAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	float MinPushbackAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	bool bCanUse = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast Effector")
	float Cooldown = 1;
	
public:	
	ABlastEffector();

	/**
	 * This will start the blast logic.
	 * A core aspect of this logic is done using the sphere trace by channel.
	 * For the moment, I am doing the spherecast in blueprint, so this method will need to be overridden and have logic constructed using the methods in this class and within blueprints.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Blast Effector")
	void UseBlast(const float ExtraBoostAmount);

	/** Handles the core blast logic outside of the sphere cast */
	UFUNCTION(BlueprintCallable, Category = "Blast Effector")
	void HandleBlast(const FHitResult& HitResult, const float ExtraBoostAmount);
	
	/** Get the start and end locations for the trace.*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Blast Effector")
	void CalculateTraceStartAndEndPositions(FVector& Start, FVector& End) const;
};
