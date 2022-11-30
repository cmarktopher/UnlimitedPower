// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelTransition.generated.h"

UINTERFACE(MinimalAPI)
class ULevelTransition : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface allowing for level transitioning
 */
class PROJECTCLICHE_API ILevelTransition
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Level Management")
	void TransitionToNewLevel(FName LevelName);
};
