// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Combat/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	
}

void UHealthComponent::BeginPlay()
{
	CurrentHealth = DefaultMaxHealth;
	MaxHealth = DefaultMaxHealth;
	
	Super::BeginPlay();
}

void UHealthComponent::GetHealthValues(float& CurrentHealthValue, float& MaxHealthValue) const
{
	CurrentHealthValue = CurrentHealth;
	MaxHealthValue = MaxHealth;
}

void UHealthComponent::ReduceCurrentHealth(const float Amount)
{
	CurrentHealth -= Amount;

	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}

	OnCurrentHealthDecreased.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth == 0)
	{
		OnHealthZero.Broadcast();
	}
}

void UHealthComponent::IncreaseCurrentHealth(const float Amount)
{
	CurrentHealth += Amount;

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}

	OnCurrentHealthIncreased.Broadcast(CurrentHealth, MaxHealth);
}
