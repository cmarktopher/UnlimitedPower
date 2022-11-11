// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Enemies/Enemy.h"
#include "Characters/Combat/HealthComponent.h"

AEnemy::AEnemy()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

AActor* AEnemy::GetSplinePatrolActor() const
{
	if (bPatrolViaSplinePoints && SplinePatrolActor)
	{
		return SplinePatrolActor;
	}

	return nullptr;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

