// Action Combat

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EEnemyState
{
	IDLE UMETA(DisplayName = "Idle"),
	RANGE UMETA(DisplayName = "Range"),
	CHARGE UMETA(DisplayName = "Charge"),
	MELEE UMETA(DisplayName = "Melee")
};