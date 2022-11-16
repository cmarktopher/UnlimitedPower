// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Combat/Damageable.h"
#include "Characters/Combat/PerceptionTag.h"
#include "GameFramework/Character.h"
#include "Levels/Triggers/InstructionTriggerReceiver.h"
#include "PlayerCharacter.generated.h"

// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInstructionTriggerActivated, FText, InstructionText);

UCLASS(Abstract, BlueprintType, Blueprintable)
class APlayerCharacter : public ACharacter,
public IDamageable, public IInstructionTriggerReceiver, public IPerceptionTag
{
	GENERATED_BODY()

	/** Scene components. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCameraComponent;
	
	/** Actor components. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UBoostComponent* BoostComponent;
	
public:
	/** Events */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInstructionTriggerActivated OnInstructionTriggerActivated;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Perception")
	FName AIPerceptionTag;
	
private:
	float OriginalJumpValue;
	
public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	
	/**
	 * Allow the camera to rotate around the Z-Axis (Yaw)
	 * @note The turn rate will be based on values set on a custom blueprint Player Controller.
	 */
	UFUNCTION(BlueprintCallable,Category = "Character | Camera Control")
	void LookRightLeft(float AxisValue);

	/**
	 * Allow the camera to rotate around the Y-Axis (Pitch)
	 * @note The turn rate will be based on values set on a custom blueprint Player Controller.
	 */
	UFUNCTION(BlueprintCallable,Category = "Character | Camera Control")
	void LookUpDown(float AxisValue);

	/** Allow forward/backward movement */ 
	UFUNCTION(BlueprintCallable,Category = "Character | Movement")
	void MoveForwardBackward(float AxisValue);

	/** Allow right/left movement */
	UFUNCTION(BlueprintCallable,Category = "Character | Movement")
	void MoveRightLeft(float AxisValue);

	/** Custom-ish jump method which will handle the amount of extra jump applied based on the boost factor. */
	UFUNCTION(BlueprintCallable, Category = "Character | Movement")
	void JumpWithBoost(float BoostAmount);

	/** Response event when the movement mode changes. */
	UFUNCTION(BlueprintCallable, Category = "Character | Movement")
	void OnMovementModeChangedResponse(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	/** Interface implementations */
	virtual void DoDamage_Implementation(AActor* DamagingActor, float Damage) override;
	virtual void NotifyInstructionActivationEvent_Implementation(const FText& InstructionsText) override;
	virtual FName GetAIPerceptionTag_Implementation() override;
};
