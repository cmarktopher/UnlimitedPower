// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Enemies/Enemy.h"

AEnemy::AEnemy()
{

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

