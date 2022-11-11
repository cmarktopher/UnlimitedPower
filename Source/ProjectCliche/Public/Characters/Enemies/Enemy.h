// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS(Abstract)
class AEnemy : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	
public:
	AEnemy();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	class UBehaviorTree* DefaultBehaviourTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	bool bPatrolViaSplinePoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Behaviour")
	AActor* SplinePatrolActor;;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI | Behaviour" )
	AActor* GetSplinePatrolActor() const;

protected:
	virtual void BeginPlay() override;
};
