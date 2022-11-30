// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.generated.h"

/**
 * Struct to contain all the settings that can be changed.
 */
USTRUCT(BlueprintType)
struct FSettingsData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 Resolution_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 Resolution_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int ShadowQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int GlobalIlluminationQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int ShadingQuality;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int ViewDistanceQuality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int VisualEffectQuality;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int TextureQuality;
};
