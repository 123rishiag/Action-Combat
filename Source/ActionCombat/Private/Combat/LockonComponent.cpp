// Action Combat


#include "Combat/LockonComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/Enemy.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CurrentTargetActor))
	{
		return;
	}

	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FVector TargetLocation = CurrentTargetActor->GetActorLocation();

	double TargetDistance = FVector::Distance(
		CurrentLocation,
		TargetLocation
	);

	if (TargetDistance >= BreakDistance)
	{
		EndLockon();
		return;
	}

	TargetLocation.Z -= 125.f;

	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(
		CurrentLocation,
		TargetLocation
	);
	Controller->SetControlRotation(NewRotation);
}

void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerRef = GetOwner<ACharacter>();
	Controller = GetWorld()->GetFirstPlayerController();
	MovementComp = OwnerRef->GetCharacterMovement();
	SpringArmComp = OwnerRef->FindComponentByClass<USpringArmComponent>();

	if (!IsValid(OwnerRef) || !IsValid(Controller) || !IsValid(MovementComp) || !IsValid(SpringArmComp))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 
				5.0f, 
				FColor::Green,
				TEXT("Some Components are not valid in Lockon Components!")
			);
		}
	}
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult;
	FVector CurrentLocation = OwnerRef->GetActorLocation();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams IgnoreParams = FCollisionQueryParams(
		FName(TEXT("Ignore Collision Params")),
		false,
		OwnerRef
	);

	bool bHasFoundTarget = GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere,
		IgnoreParams
	);

	if (!bHasFoundTarget)
	{
		return;
	}

	if (!OutResult.GetActor()->Implements<UEnemy>())
	{
		return;
	}

	CurrentTargetActor = OutResult.GetActor();

	MovementComp->bOrientRotationToMovement = false;
	MovementComp->bUseControllerDesiredRotation = true;
	SpringArmComp->TargetOffset = FVector(0.f, 0.f, 100.f);

	Controller->SetIgnoreLookInput(true);

	IEnemy::Execute_OnSelect(CurrentTargetActor);
}

void ULockonComponent::EndLockon()
{
	IEnemy::Execute_OnDeselect(CurrentTargetActor);

	CurrentTargetActor = nullptr;

	MovementComp->bOrientRotationToMovement = true;
	MovementComp->bUseControllerDesiredRotation = false;
	SpringArmComp->TargetOffset = FVector::ZeroVector;

	Controller->ResetIgnoreLookInput();
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		EndLockon();
	}
	else
	{
		StartLockon(Radius);
	}
}

