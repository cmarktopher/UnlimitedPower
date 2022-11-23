// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Combat/Damageable.h"
#include "Characters/Combat/Attacker.h"
#include "Characters/Combat/PerceptionTag.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "Enemy.generated.h"

struct FAIStimulus;
UCLASS(Abstract)
class AEnemy : public ACharacter,
public IDamageable, public IAttacker,  public IPerceptionTag
{
	GENERATED_BODY()

	// Scene components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* HealthBarComponent;
	
	// Actor components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	//UAIPerceptionComponent* AIPerceptionComponent;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Perception")
	FName AIPerceptionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	class UBehaviorTree* DefaultBehaviourTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	bool bPatrolViaSplinePoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	AActor* SplinePatrolActor;;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI | Behaviour")
	class AEnemyAIController* AIController; 
	
public:
	AEnemy();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI | Behaviour" )
	AActor* GetSplinePatrolActor() const;
	
protected:
	virtual void BeginPlay() override;

	/** Process perception stimuli caused by other actors (will be player only for now) */
	UFUNCTION(BlueprintCallable, Category = "AI Controller | Behaviour")
	void ProcessSightPerceptionStimuli(AActor* ActorProducingStimuli, UPARAM(ref) const FAIStimulus& Stimuli, const FName& BlackboardKey);
	
	/**
	 * Response to when health reaches zero
	 * By default, the character will be destroyed but can be overriden in blueprints for some extra logic (death animation etc...)
	 * TODO This is also repeated in the player class - will look into making a general character parent class for this type of logic after the game jam.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character | Health")
	void HandleHealthZeroResponse();

	virtual FName GetAIPerceptionTag_Implementation() override;
};
