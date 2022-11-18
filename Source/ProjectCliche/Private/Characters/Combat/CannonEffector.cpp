// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Combat/CannonEffector.h"

ACannonEffector::ACannonEffector()
{


}

void ACannonEffector::BeginPlay()
{
	CurrentCannonRange = MinCannonRange;
	Super::BeginPlay();
}

void ACannonEffector::UseCannon_Implementation(const float ExtraBoostAmount)
{
	GetWorld()->GetTimerManager().SetTimer(
		ChannelTimerHandler,
		this,
		&ACannonEffector::HandleCannon,
		0.1,
		true
	);
}

void ACannonEffector::HandleCannon_Implementation()
{
	// Will do this in blueprints - trace handling is less painfull there.
}

void ACannonEffector::ReleaseCannon_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(ChannelTimerHandler);
}

void ACannonEffector::CalculateTraceStartAndEndPositions(FVector& Start, FVector& End) const
{
	Start = GetActorLocation();

	End = Start + (GetActorForwardVector() * CurrentCannonRange);
}


