// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Controllers/EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"

AEnemyAIController::AEnemyAIController()
{

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::ProcessSightPerceptionStimuli(AActor* ActorProducingStimuli, const FAIStimulus& Stimuli, const FName& BlackboardKey)
{
	// TODO Does not distinguish between different perception stimuli at the moment, will update if game needs extra stimuli (also, I have no idea how to get the stimuli types at the moment)

	// This conditional handles logic for when we are within sight and when out of site - mostly just setting blackboard values and letting the behaviour tree handle the logic.
	if (Stimuli.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(BlackboardKey, ActorProducingStimuli);
	}
	else
	{
		Blackboard->SetValueAsObject(BlackboardKey, nullptr);
	}
}
