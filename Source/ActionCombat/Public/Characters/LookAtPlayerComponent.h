// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LookAtPlayerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULookAtPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULookAtPlayerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	bool bCanRotate = false;

protected:
	virtual void BeginPlay() override;
		
private:
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 400.f;
};
