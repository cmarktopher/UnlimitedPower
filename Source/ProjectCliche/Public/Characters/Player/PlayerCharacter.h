// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Combat/Damageable.h"
#include "Characters/Combat/PerceptionTag.h"
#include "GameFramework/Character.h"
#include "Levels/Triggers/DialogueTriggerReceiver.h"
#include "Levels/Triggers/InstructionTriggerReceiver.h"
#include "PlayerCharacter.generated.h"

/**
 * States for the player
 */
UENUM(BlueprintType)
enum EPlayerState
{
	Normal,
	InCutscene
};


// Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInstructionTriggerActivated, FText, InstructionText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerStateSwitched, EPlayerState, PreviousState, EPlayerState, CurrentState);

UCLASS(Abstract, BlueprintType, Blueprintable)
class APlayerCharacter : public ACharacter,
public IDamageable, public IInstructionTriggerReceiver, public IDialogueTriggerReceiver , public IPerceptionTag
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

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerStateSwitched OnPlayerStateSwitched;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player State")
	TEnumAsByte<EPlayerState> CurrentPlayerState = EPlayerState::Normal;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI | Perception")
	FName AIPerceptionTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jumping")
	float BaseDoubleJumpAmount = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jumping")
	int32 MaxJumpCount = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat System")
	class ABlastEffector* BlastWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat System")
	class ACannonEffector* CannonWeapon;
	
private:
	bool bIsInFirstJump = false;
	int32 CurrentJumpCount;
	
public:
	APlayerCharacter();

	/** Method used for state switching */
	UFUNCTION(BlueprintCallable, Category = "Player State")
	void SwitchPlayerState(TEnumAsByte<EPlayerState> NewState);

	/**
	 * Get the current jump count
	 * TODO Seems like Unreal already has a mechanism to keep track of jump count. Will move to that system once the jam is over.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character | Movement")
	int32 GetJumpCount() const;
	
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

	/** A custom-ish jump method that will have logic for double jumping */
	UFUNCTION(BlueprintCallable, Category = "Character | Movement")
	void JumpWithDoubleJump(const float BoostAmount, USoundBase* JumpSound);

	/** Response event when the movement mode changes. */
	UFUNCTION(BlueprintCallable, Category = "Character | Movement")
	void OnMovementModeChangedResponse(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	/** Method to line trace to check if we are above a surface. This is implemented in blueprints for now. */
	UFUNCTION(BlueprintImplementableEvent, Category = "Character | Movement")
	bool CheckIfGroundUnderPlayer();

	/**
	 * Response to when health reaches zero
	 * By default, the character will be destroyed but can be overriden in blueprints for some extra logic (death animation etc...)
	 * TODO This is also repeated in the enemy class - will look into making a general character parent class for this type of logic after the game jam.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character | Health")
	void HandleHealthZeroResponse();
	
	/** Interface implementations */
	virtual void DoDamage_Implementation(AActor* DamagingActor, float Damage) override;
	virtual void NotifyInstructionActivationEvent_Implementation(const FText& InstructionsText) override;
	virtual void ReceiveDialogue_Implementation(const int DialogueTextIdentifier) override;
	virtual FName GetAIPerceptionTag_Implementation() override;
};


