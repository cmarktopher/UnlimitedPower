// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Combat/BlastEffector.h"
#include "Characters/Combat/Damageable.h"
#include "Kismet/KismetMathLibrary.h"

ABlastEffector::ABlastEffector()
{
	
}

void ABlastEffector::UseBlast_Implementation()
{
	// Blank for now, decided to do the sphere trace in blueprints.
}

void ABlastEffector::HandleBlast(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	
	const float DistanceRatio = FVector::Distance(GetActorLocation(), HitActor->GetActorLocation()) / BlastDistance;
	const FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), HitActor->GetActorLocation());

	// Do damage and perform knock back on enemies
	if (HitActor->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
	{
		// Handle interpolating damage based on distance factor
		const float Damage = UKismetMathLibrary::Lerp(BlastDamage, 0, DistanceRatio);
		
		IDamageable::Execute_DoDamage(HitActor, this, Damage);

		// Handle interpolating velocity of knock back based on distance factor
		const FVector PushbackVelocity = UKismetMathLibrary::VLerp(MaxPushbackAmount * Direction, MinPushbackAmount * Direction, DistanceRatio);
		IDamageable::Execute_PerformPushback(HitActor, this, PushbackVelocity);
	}
}

void ABlastEffector::CalculateTraceStartAndEndPositions(FVector& Start, FVector& End) const
{
	Start = GetActorLocation();

	End = Start + (GetActorForwardVector() * BlastDistance);
}



