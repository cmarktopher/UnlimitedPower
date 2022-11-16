// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PerceptionTag.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPerceptionTag : public UInterface
{
	GENERATED_BODY()
};

/**
 * Temporary solution to get the assigned perception tag to distinguish Player and Enemy actors.
 */
class IPerceptionTag
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AI | Behaviour")
	FName GetAIPerceptionTag();
};
