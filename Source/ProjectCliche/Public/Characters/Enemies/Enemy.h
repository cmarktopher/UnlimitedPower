// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Combat/Damageable.h"
#include "Characters/Combat/Attacker.h"
#include "Characters/Combat/PerceptionTag.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS(Abstract)
class AEnemy : public ACharacter,
public IDamageable, public IAttacker,  public IPerceptionTag
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Perception")
	FName AIPerceptionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	class UBehaviorTree* DefaultBehaviourTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	bool bPatrolViaSplinePoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	AActor* SplinePatrolActor;;
	
public:
	AEnemy();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI | Behaviour" )
	AActor* GetSplinePatrolActor() const;
	
protected:
	virtual void BeginPlay() override;

	virtual FName GetAIPerceptionTag_Implementation() override;
};
