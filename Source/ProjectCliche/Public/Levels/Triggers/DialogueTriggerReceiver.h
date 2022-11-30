// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogueTriggerReceiver.generated.h"

UINTERFACE(MinimalAPI)
class UDialogueTriggerReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for the player to receive dialogue from triggers.
 */
class IDialogueTriggerReceiver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Dialogue")
	void ReceiveDialogue(const int DialogueTextIdentifier);
};
