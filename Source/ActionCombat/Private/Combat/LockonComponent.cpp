// Action Combat


#include "Combat/LockonComponent.h"

ULockonComponent::ULockonComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ULockonComponent::StartLockon()
{
	UE_LOG(LogTemp, Warning, TEXT("Lockon Started!"));
}

