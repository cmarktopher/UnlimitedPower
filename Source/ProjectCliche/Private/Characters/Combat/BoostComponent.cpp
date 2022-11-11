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
}


