// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Combat/BoostComponent.h"
#include "Characters/Combat/HealthComponent.h"

UBoostComponent::UBoostComponent()
{

}

void UBoostComponent::BeginPlay()
{
	// Set defaults
	MaxBoost = DefaultMaxBoost;
	
	Super::BeginPlay();
}

void UBoostComponent::GetBoostValues(float& CurrentBoostValue, float& MaxBoostValue) const
{
	CurrentBoostValue = CurrentBoost;
	MaxBoostValue = MaxBoost;
}

void UBoostComponent::IncreaseBoost(const float Amount)
{
	CurrentBoost += Amount * BoostFactor;

	if (CurrentBoost >= MaxBoost)
	{
		CurrentBoost = MaxBoost;
	}
	
	OnCurrentBoostIncreased.Broadcast(CurrentBoost, MaxBoost);

	// Since we want to decrease the boost amount over time, lets use a timer handler for that until it reaches 0.
	GetWorld()->GetTimerManager().ClearTimer(BoostDecayTimerHandler);
	
	GetWorld()->GetTimerManager().SetTimer(
		BoostDecayTimerHandler,
		this,
		&UBoostComponent::DecreaseBoostOverTime,
		BoostDecayRate,
		true);
}


void UBoostComponent::DecreaseBoostOverTime()
{
    //UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentBoost)
	CurrentBoost -= BoostDecayAmount;
	
	if (CurrentBoost <= 0)
	{
		OnBoostReachedZero.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(BoostDecayTimerHandler);
	}
}

