// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/BarWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMathLibrary.h"

void UBarWidget::NativeConstruct()
{
	
	Super::NativeConstruct();
}

void UBarWidget::UpdateProgressBar(const float CurrentValue, const float MaxValue)
{
	TargetProgressValue = CurrentValue / MaxValue;
	
	CurrentProgressValue = ProgressBar->Percent;

	if (TargetProgressValue <= CurrentProgressValue)
	{
		GetWorld()->GetTimerManager().SetTimer(
			ProgressBarInterpolationTimeHandler,
			this,
			&UBarWidget::InterpolateProgressBarDownwards,
			0.01,
			true);
	}

	if (TargetProgressValue >= CurrentProgressValue)
	{
		GetWorld()->GetTimerManager().SetTimer(
			ProgressBarInterpolationTimeHandler,
			this,
			&UBarWidget::InterpolateProgressBarUpwards,
			0.01,
			true);
	}
}

void UBarWidget::InterpolateProgressBarDownwards()
{
	CurrentProgressValue = UKismetMathLibrary::FInterpTo_Constant(
		CurrentProgressValue,
		TargetProgressValue,
		GetWorld()->DeltaTimeSeconds,
		2
	);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentProgressValue)
	
	ProgressBar->SetPercent(CurrentProgressValue);

	if (CurrentProgressValue <= TargetProgressValue)
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressBarInterpolationTimeHandler);
	}
}

void UBarWidget::InterpolateProgressBarUpwards()
{
	CurrentProgressValue = UKismetMathLibrary::FInterpTo_Constant(
		CurrentProgressValue,
		TargetProgressValue,
		GetWorld()->DeltaTimeSeconds,
		2
	);

	//UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentProgressValue)
	
	ProgressBar->SetPercent(CurrentProgressValue);

	if (CurrentProgressValue >= TargetProgressValue)
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressBarInterpolationTimeHandler);
	}
}
