// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Enemies/Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Combat/HealthComponent.h"
#include "Characters/Controllers/EnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "UserInterface/BarWidget.h"

AEnemy::AEnemy()
{
	// Create our actor components
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	// Create our scene components
	//AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")); // I will handle this in blueprints - can't set the perception sense class in blueprints for some reason if done through c++.
	
	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Component"));
	HealthBarComponent->SetupAttachment(RootComponent);
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void AEnemy::BeginPlay()
{
	// If we have a behaviour tree assigned, we can assume that we want to run the tree.
	if (DefaultBehaviourTree)
	{
		AIController = static_cast<AEnemyAIController*>(GetController());
		AIController->RunBehaviorTree(DefaultBehaviourTree);
	}

	// Bind events
	HealthComponent->OnHealthZero.AddDynamic(this, &AEnemy::HandleHealthZeroResponse);
	
	Super::BeginPlay();
}

void AEnemy::ProcessSightPerceptionStimuli(AActor* ActorProducingStimuli, const FAIStimulus& Stimuli, const FName& BlackboardKey)
{
	// TODO Does not distinguish between different perception stimuli at the moment, will update if game needs extra stimuli (also, I have no idea how to get the stimuli types at the moment)

	// TODO Probably not the best way to do this, but just a simple solution to ensure enemy is only targeting the player and not other enemies. Will look into the AI affiliation system in the future.
	
	if (Execute_GetAIPerceptionTag(ActorProducingStimuli) == AIPerceptionTag)
	{
		return;
	}
	
	// This conditional handles logic for when we are within sight and when out of site - mostly just setting blackboard values and letting the behaviour tree handle the logic.
	if (Stimuli.WasSuccessfullySensed())
	{
		const auto Blackboard = AIController->GetBlackboardComponent();
		Blackboard->SetValueAsObject(BlackboardKey, ActorProducingStimuli);

		// I've decided to make the health bar appear only when the enemy has sensed a target
		HealthBarComponent->SetVisibility(true);
	}
	else
	{
		HandlePerceptionLost(BlackboardKey);
	}
}

void AEnemy::HandlePerceptionLost_Implementation(const FName& BlackboardKey)
{
	const auto Blackboard = AIController->GetBlackboardComponent();
	Blackboard->SetValueAsObject(BlackboardKey, nullptr);
		
	HealthBarComponent->SetVisibility(false);
}

void AEnemy::HandleHealthZeroResponse_Implementation()
{
	OnEnemyDied.Broadcast(this);
	Destroy();
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