// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS(Abstract)
class AEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:
	AEnemy();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Behaviour")
	class UBehaviorTree* DefaultBehaviourTree;
	
	virtual void BeginPlay() override;
};
