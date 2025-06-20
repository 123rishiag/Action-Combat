// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerActionsComponent.generated.h"

class IMainPlayer;
class UCharacterMovementComponent;
class UAnimMontage;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature,
	UPlayerActionsComponent,
	OnSprintDelegate,
	float,
	Cost
); 

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnRollSignature,
	UPlayerActionsComponent,
	OnRollDelegate,
	float,
	Cost
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerActionsComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void Walk();

	UFUNCTION(BlueprintCallable)
	void Roll();

	UFUNCTION()
	void FinishRollAnim();

	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate; 
	
	UPROPERTY(BlueprintAssignable)
	FOnRollSignature OnRollDelegate;

	bool bIsRollActive = false;

protected:
	virtual void BeginPlay() override;
		
private:
	ACharacter* CharacterRef;
	UCharacterMovementComponent* MovementComp;
	IMainPlayer* IPlayerRef;

	UPROPERTY(EditAnywhere)
	float SprintCost = 0.1f;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere)
	UAnimMontage* RollAnimMontage;

	UPROPERTY(EditAnywhere)
	float RollCost = 5.f;
};
