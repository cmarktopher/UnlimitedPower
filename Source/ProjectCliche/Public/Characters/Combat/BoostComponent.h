// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoostComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentBoostModified, float, CurrentBoost, float, MaxBoost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoostReachedZero);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UBoostComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Boost System")
	FOnCurrentBoostModified OnCurrentBoostIncreased;

	UPROPERTY(BlueprintAssignable, Category = "Boost System")
	FOnBoostReachedZero OnBoostReachedZero;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Boost System")
	float DefaultMaxBoost = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boost System")
	float BoostFactor = 1.2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boost System")
	float MaxBoost = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Boost System")
	float CurrentBoost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Boost System")
	float BoostDecayAmount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Boost System")
	float BoostDecayRate = 0.5;
	
private:
	FTimerHandle BoostDecayTimerHandler;
	
public:	
	UBoostComponent();
	
protected:
	virtual void BeginPlay() override;
	
public:
	/** Get the current and max health */
	UFUNCTION(BlueprintCallable, Category = "Boost System")
	void GetBoostValues(float& CurrentBoostValue, float& MaxBoostValue) const;
	
	/** 
	 * Increase current boost value
	 */
	UFUNCTION(BlueprintCallable, Category = "Boost System")
	void IncreaseBoost(const float Amount);

	/** Decrease boost over time */
	UFUNCTION(BlueprintCallable, Category = "Blast Effector")
	void DecreaseBoostOverTime();
};

