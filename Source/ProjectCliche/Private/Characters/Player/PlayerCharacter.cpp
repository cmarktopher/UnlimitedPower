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
	// Set some defaults
	OriginalJumpValue = GetCharacterMovement()->JumpZVelocity;
	
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

void APlayerCharacter::JumpWithBoost(const float BoostAmount)
{
	// Set the jump amount - we will need to reset the jump amount back to the original amount once character lands.
	GetCharacterMovement()->JumpZVelocity += BoostAmount;

	// Jump
	Jump();
}

void APlayerCharacter::OnMovementModeChangedResponse(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	switch (PrevMovementMode)
	{
		case MOVE_None:
			break;
		case MOVE_Walking:
			// For jumping logic, we want to reset the jump z value back to the original value.
			GetCharacterMovement()->JumpZVelocity = OriginalJumpValue;
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





