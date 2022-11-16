// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Enemies/Enemy.h"
#include "Characters/Combat/HealthComponent.h"
#include "Characters/Controllers/EnemyAIController.h"

AEnemy::AEnemy()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AEnemy::BeginPlay()
{
	// If we have a behaviour tree assigned, we can assume that we want to run the tree.
	if (DefaultBehaviourTree)
	{
		AEnemyAIController* AIController =  static_cast<AEnemyAIController*>(GetController());
		AIController->RunBehaviorTree(DefaultBehaviourTree);
	}
	
	Super::BeginPlay();
}

FName AEnemy::GetAIPerceptionTag_Implementation()
{
	return AIPerceptionTag;
}

AActor* AEnemy::GetSplinePatrolActor() const
{
	if (bPatrolViaSplinePoints && SplinePatrolActor)
	{
		return SplinePatrolActor;
	}

	return nullptr;
}