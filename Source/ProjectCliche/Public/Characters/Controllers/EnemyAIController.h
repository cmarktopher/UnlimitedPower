// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

/**
 * AI Controller for enemies
 */
UCLASS()
class AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "AI Controller | Behaviour")
	void ProcessSightPerceptionStimuli(AActor* ActorProducingStimuli, UPARAM(ref) const FAIStimulus& Stimuli, const FName& BlackboardKey);
};
