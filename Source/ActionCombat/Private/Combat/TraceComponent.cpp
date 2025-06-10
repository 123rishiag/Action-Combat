// Action Combat


#include "Combat/TraceComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DamageEvents.h"
#include "Interfaces/Fighter.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsAttacking) 
	{ 
		return; 
	}

	// Fetching Start and End of Area for which trace needs to work
	FVector StartSocketLocation = SkeletalComp->GetSocketLocation(Start);
	FVector EndSocketLocation = SkeletalComp->GetSocketLocation(End);
	FQuat ShapeRotation = SkeletalComp->GetSocketQuaternion(Rotation);

	TArray<FHitResult> OutResults;
	double WeaponDistance = FVector::Distance(StartSocketLocation, EndSocketLocation);

	FVector BoxHalfExtent = FVector(
		BoxCollisionLength, BoxCollisionLength, WeaponDistance
	);
	BoxHalfExtent /= 2;

	FCollisionShape Box = FCollisionShape::MakeBox(BoxHalfExtent);

	FCollisionQueryParams IgnoreParams = FCollisionQueryParams(
		FName (TEXT("Ignore Params")),
		false,
		GetOwner()
	);

	// Starting Trace
	bool bHasFoundTargets = GetWorld()->SweepMultiByChannel(
		OutResults,
		StartSocketLocation,
		EndSocketLocation,
		ShapeRotation,
		ECollisionChannel::ECC_GameTraceChannel1,
		Box,
		IgnoreParams
	);

	// Drawing Debug Box
	if (bDebugMode)
	{
		FVector CenterPoint = 
			UKismetMathLibrary::VLerp(
				StartSocketLocation, EndSocketLocation, 0.5f
			);

		UKismetSystemLibrary::DrawDebugBox(
			GetWorld(),
			CenterPoint,
			Box.GetExtent(),
			bHasFoundTargets ? FLinearColor::Green : FLinearColor::Red,
			ShapeRotation.Rotator(),
			1.0f,
			2.0f
		);
	}

	if (OutResults.Num() == 0) 
	{ 
		return; 
	}

	// If any object is traced, go forward
	float CharacterDamage = 0.0f;

	IFighter* FighterRef = Cast<IFighter>(GetOwner());

	if (FighterRef)
	{
		CharacterDamage = FighterRef->GetDamage();
	}

	// If the object traced is a fighter, apply damage
	FDamageEvent TargetAttackedEvent;

	for (const FHitResult& Hit : OutResults)
	{
		AActor* TargetActor = Hit.GetActor();

		if (TargetsToIgnore.Contains(TargetActor)) 
		{ 
			continue; 
		}

		TargetActor->TakeDamage(
			CharacterDamage,
			TargetAttackedEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
		);

		TargetsToIgnore.AddUnique(TargetActor);
	}
}

void UTraceComponent::HandleResetAttack()
{
	TargetsToIgnore.Empty();
}

void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	SkeletalComp = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

}

