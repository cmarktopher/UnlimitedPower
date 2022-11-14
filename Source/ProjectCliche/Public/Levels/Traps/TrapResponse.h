// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TrapResponse.generated.h"

UINTERFACE(MinimalAPI)
class UTrapResponse : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to communicate with actors to handle trap related logic.
 */
class ITrapResponse
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trap")
	void Activate(AActor* TriggerActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trap")
	void Deactivate(AActor* TriggerActor);
};
