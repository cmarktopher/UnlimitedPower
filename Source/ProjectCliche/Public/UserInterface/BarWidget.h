// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BarWidget.generated.h"

/**
 * Base class for bar widgets such as health, experience and booster bars (can include more if new idea comes)
 */
UCLASS(Abstract)
class UBarWidget : public UUserWidget
{
	GENERATED_BODY()

	/** Widgets that need binding in blueprints. */
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ProgressBar;

	/** Properties for interpolation of progress bar values */
	FTimerHandle ProgressBarInterpolationTimeHandler;
	float TargetProgressValue;
	float CurrentProgressValue;
	
protected:
	virtual void NativeConstruct() override;

	/** Update the progress bar. */
	UFUNCTION(BlueprintCallable, Category = "Progress Bar")
	void UpdateProgressBar(const float CurrentValue, const float MaxValue);

private:
	/**
	 * Interpolate the current bar percent value towards the target percent value.
	 * Essentially, this will make the fill amount move towards the target value to provide a smoother look.
	 * There are two versions of the method with slightly different logic to handle exiting the timer handler (could have a more elegant way to do this, but will work for now).
	 */
	void InterpolateProgressBarDownwards();
	void InterpolateProgressBarUpwards();
	
};
