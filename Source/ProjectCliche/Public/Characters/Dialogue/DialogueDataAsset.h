// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueDataAsset.generated.h"

/**
 * Data Asset for dialogue.
 */
UCLASS(Blueprintable, BlueprintType)
class UDialogueDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dialogue Data")
	TMap<int, FText> Dialogue;
	
};
