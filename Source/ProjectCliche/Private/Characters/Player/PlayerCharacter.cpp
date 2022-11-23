// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Characters/Combat/BoostComponent.h"
#include "Characters/Combat/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Kismet/KismetMathLibrary.h"

APlayerCharacter::APlayerCharacter()
{
	// Set up scene component instantiation and respective attachments
	CameraBoomComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom Compoennt"));
	CameraBoomComponent->SetupAttachment(RootComponent);

	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	ThirdPersonCameraComponent->SetupAttachment(CameraBoomComponent, USpringArmComponent::SocketName);

	// Instantiate actor components
	PerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimuli Source Component"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	BoostComponent = CreateDefaultSubobject<UBoostComponent>(TEXT("Boost Component"));
}

void APlayerCharacter::BeginPlay()
{
	// Bind events
	MovementModeChangedDelegate.AddDynamic(this, &APlayerCharacter::OnMovementModeChangedResponse);
	
	Super::BeginPlay();
}

void APlayerCharacter::LookRightLeft(const float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::LookUpDown(const float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::MoveForwardBackward(const float AxisValue)
{
	// Get the rotation of the controller, calculate forward vector and move accordingly
	const FRotator ControllerYawRotation(0, GetControlRotation().Yaw, 0);
	const FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(ControllerYawRotation);

	AddMovementInput(ForwardDirection, AxisValue);
}

void APlayerCharacter::MoveRightLeft(const float AxisValue)
{
	// Get the rotation of the controller, calculate right vector and move accordingly
	const FRotator ControllerYawRotation(0, GetControlRotation().Yaw, 0);
	const FVector RightDirection = UKismetMathLibrary::GetRightVector(ControllerYawRotation);

	AddMovementInput(RightDirection, AxisValue);
	
}

void APlayerCharacter::JumpWithDoubleJump(const float BoostAmount)
{
	// Do the initial jump
	if (CurrentJumpCount == 0)
	{
		Jump();
	}
	else if (CurrentJumpCount < MaxJumpCount)
	{
		// To handle the subsequent jump, we will use launch character.
		// However, since this is intended to be propelled from the ground, we need to check if we have ground directly under us.
		// I'll use a trace to handle this in blueprints which will override the following method.
		if (CheckIfGroundUnderPlayer())
		{
			LaunchCharacter(GetActorUpVector() * (BaseDoubleJumpAmount + BoostAmount), false, false);
		}
		
	}

	CurrentJumpCount++;
}

void APlayerCharacter::OnMovementModeChangedResponse(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	switch (GetCharacterMovement()->MovementMode)
	{
		case MOVE_None:
			break;
		case MOVE_Walking:
			CurrentJumpCount = 0;
			break;
		case MOVE_NavWalking:
			break;
		case MOVE_Falling:
			break;
		case MOVE_Swimming:
			break;
		case MOVE_Flying:
			break;
		case MOVE_Custom:
			break;
		case MOVE_MAX:
			break;
		default: ;
		
	}
}

void APlayerCharacter::DoDamage_Implementation(AActor* DamagingActor, const float Damage)
{
	IDamageable::DoDamage_Implementation(DamagingActor, Damage);

	HealthComponent->ReduceCurrentHealth(Damage);
	BoostComponent->IncreaseBoost(Damage);
}

void APlayerCharacter::NotifyInstructionActivationEvent_Implementation(const FText& InstructionsText)
{
	OnInstructionTriggerActivated.Broadcast(InstructionsText);
}

FName APlayerCharacter::GetAIPerceptionTag_Implementation()
{
	return AIPerceptionTag;
}





