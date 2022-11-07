// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Enemies/Enemy.h"

#include "AIController.h"

AEnemy::AEnemy()
{

}

void AEnemy::BeginPlay()
{
	// We want the enemy to start running the set behaviour tree.
	CachedAIController = static_cast<AAIController*>(GetController());
	CachedAIController->RunBehaviorTree(DefaultBehaviourTree);

	Super::BeginPlay();
}
