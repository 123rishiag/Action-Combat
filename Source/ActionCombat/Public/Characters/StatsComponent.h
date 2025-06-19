// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/EStat.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnHealthPercentUpdateSignature,
	UStatsComponent,
	OnHealthPercentUpdateDelegate,
	float,
	Percentage
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnStaminaPercentUpdateSignature,
	UStatsComponent,
	OnStaminaPercentUpdateDelegate,
	float,
	Percentage
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(
	FOnZeroHealthSignature,
	UStatsComponent,
	OnZeroHealthDelegate
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatsComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere)
	TMap<TEnumAsByte<EStat>, float> Stats;

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float Amount);

	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float Amount);

	UFUNCTION(BlueprintCallable)
	void RegenStamina();

	UFUNCTION()
	void EnableStaminaRegen();

	UFUNCTION(BlueprintPure)
	float GetStatPercentage(EStat Current, EStat Max);

	UPROPERTY(BlueprintAssignable)
	FOnHealthPercentUpdateSignature OnHealthPercentUpdateDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnStaminaPercentUpdateSignature OnStaminaPercentUpdateDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnZeroHealthSignature OnZeroHealthDelegate;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	double StaminaRegenRate = 10.f;

	UPROPERTY(VisibleAnywhere)
	bool bCanStaminaRegen = true;

	UPROPERTY(EditAnywhere)
	float StaminaDelayDuration = 2.0f;
};
