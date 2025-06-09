// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewTargetActorRef);
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentSpeed = 0.f;

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();

	UFUNCTION(BlueprintCallable)
	void UpdateDirection();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInCombat = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentDirection = 0.f;

};
