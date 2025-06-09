// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONCOMBAT_API IEnemy
{
	GENERATED_BODY()

public:
	/// Use BlueprintImplementableEvent in UFUNCTION Macro to call it from BossCharacter Blueprint EventGraph instead of code
	/// in that case it is not necessary to implement OnSelect_Implementation in the classes inheriting from this interface.
	UFUNCTION(BlueprintNativeEvent)
	void OnSelect();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeselect();

};
