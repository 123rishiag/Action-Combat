// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCharging = false;

};
