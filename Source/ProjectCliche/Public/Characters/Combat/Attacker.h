// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Attacker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttacker : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for actors that can cause attack.
 * Will mostly be used for AI entities where the behaviour tree task will call the methods defined here to get the AI to attack.
 */
class IAttacker
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack System")
	void Attack(AActor* AttackedActor);
};
