// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCurrentHealthModified, float, CurrentHealth, float, MaxHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Health System")
	FOnCurrentHealthModified OnCurrentHealthIncreased;

	UPROPERTY(BlueprintAssignable, Category = "Health System")
	FOnCurrentHealthModified OnCurrentHealthDecreased;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health System")
	float DefaultMaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health System")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health System")
	float CurrentHealth;
	
public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Get the current and max health */
	UFUNCTION(BlueprintCallable, Category = "Health System")
	void GetHealthValues(float& CurrentHealthValue, float& MaxHealthValue) const;
	
	/** Reduce current health. Good for handling damage mechanics. */
	UFUNCTION(BlueprintCallable, Category = "Health System")
	void ReduceCurrentHealth(float Amount);

	/** Increase current health. Good for handling healing mechanics. */
	UFUNCTION(BlueprintCallable, Category = "Health System")
	void IncreaseCurrentHealth(float Amount);
		
};
