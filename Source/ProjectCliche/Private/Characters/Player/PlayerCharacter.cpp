// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
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





