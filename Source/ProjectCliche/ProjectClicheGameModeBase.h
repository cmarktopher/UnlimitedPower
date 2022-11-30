// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "General/GameStructs.h"
#include "Levels/LevelTransition.h"
#include "ProjectClicheGameModeBase.generated.h"

/**
 * Base game mode class to be inherited by all game modes in the game.
 */
UCLASS()
class AProjectClicheGameModeBase : public AGameModeBase, public ILevelTransition
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Management")
	FName PendingNextLevel;

public:
	/** Method to be overriden in blueprints for starting levels. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Initialization")
	void InitializeLevel();

	/** Create widgets */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Initialization")
	void CreateAndInitWidgets();

	/** Set settings */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Settings")
	void SetSettings(const FSettingsData& SettingsData);

	/** Allow for progression to next level. */
	virtual void TransitionToNewLevel_Implementation(FName LevelName) override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Level Management")
	void NextLevel();
};
