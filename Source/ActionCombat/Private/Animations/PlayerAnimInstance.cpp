// Action Combat


#include "Animations/PlayerAnimInstance.h"

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}

void UPlayerAnimInstance::UpdateSpeed()
{
	APawn* PawnRef = TryGetPawnOwner();

	if (!IsValid(PawnRef))
	{
		return;
	}

	FVector Velocity = PawnRef->GetVelocity();
	CurrentSpeed = static_cast<float>(Velocity.Length());
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef = TryGetPawnOwner();

	if (!IsValid(PawnRef))
	{
		return;
	}

	if (!bIsInCombat)
	{
		return;
	}

	// Calculate Direction returns the direction between -180 and 180
	CurrentDirection = CalculateDirection(
		PawnRef->GetVelocity(),
		PawnRef->GetActorRotation()
	);

}