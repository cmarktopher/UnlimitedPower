// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InstructionTriggerReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UInstructionTriggerReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the player to implement a method for receiving trigger events from the level involving instructions for the game.
 */
class IInstructionTriggerReceiver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Instructions System")
	void NotifyInstructionActivationEvent(const FText& InstructionsText);
};
