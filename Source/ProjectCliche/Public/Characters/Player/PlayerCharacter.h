// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Combat/Damageable.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable)
class APlayerCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

	/** Scene component for the camera and camera boom */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoomComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCameraComponent;
	
	/** Actor component for player to act as a source stimuli for the perception system.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components", meta = (AllowPrivateAccess = "true"))
	class UBoostComponent* BoostComponent;
	
public:
	APlayerCharacter();

protected:
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

	virtual void DoDamage_Implementation(AActor* DamagingActor, float Damage) override;
};
