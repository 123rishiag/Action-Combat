// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockonComponent.generated.h"

class ACharacter;
class APlayerController;
class UCharacterMovementComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature, 
	ULockonComponent,
	OnUpdatedTargetDelegate,
	AActor*,
	NewTargetActorRef
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API ULockonComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULockonComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintAssignable)
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void StartLockon(float Radius = 750.f);

	void EndLockon();

	UFUNCTION(BlueprintCallable)
	void ToggleLockon(float Radius = 750.f);

	UPROPERTY(EditAnywhere)
	double BreakDistance = 1000.f;

private:
	ACharacter* OwnerRef;
	APlayerController* Controller;
	UCharacterMovementComponent* MovementComp;
	USpringArmComponent* SpringArmComp;
};
