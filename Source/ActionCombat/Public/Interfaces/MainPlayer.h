// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MainPlayer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMainPlayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONCOMBAT_API IMainPlayer
{
	GENERATED_BODY()

public:

	virtual bool HasEnoughStamina(float Cost) { return true; }
};
