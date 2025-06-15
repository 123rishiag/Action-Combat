// Action Combat


#include "Characters/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatsComponent::ReduceHealth(float Amount)
{
	if (Stats[EStat::Health] <= 0)
	{
		return;
	}

	Stats[EStat::Health] -= Amount;
	Stats[EStat::Health] = UKismetMathLibrary::FClamp(
		Stats[EStat::Health], 
		0, 
		Stats[EStat::MaxHealth]
	);
}

void UStatsComponent::ReduceStamina(float Amount)
{
	Stats[EStat::Stamina] -= Amount;
	Stats[EStat::Stamina] = UKismetMathLibrary::FClamp(
		Stats[EStat::Stamina],
		0,
		Stats[EStat::MaxStamina]
	);

	bCanStaminaRegen = false;

	FLatentActionInfo FunctionInfo = FLatentActionInfo(
		0,
		100,
		TEXT("EnableStaminaRegen"),
		this
	);

	UKismetSystemLibrary::RetriggerableDelay(
		GetWorld(),
		StaminaDelayDuration,
		FunctionInfo
	);
}

void UStatsComponent::RegenStamina()
{
	if (!bCanStaminaRegen)
	{
		return;
	}

	Stats[EStat::Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStat::Stamina],
		Stats[EStat::MaxStamina],
		GetWorld()->DeltaTimeSeconds,
		StaminaRegenRate
	);
}

void UStatsComponent::EnableStaminaRegen()
{
	bCanStaminaRegen = true;
}

void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

