// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "FTraceSocket.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct ACTIONCOMBAT_API FTraceSocket
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Start;

	UPROPERTY(EditAnywhere)
	FName End;

	UPROPERTY(EditAnywhere)
	FName Rotation;
};
