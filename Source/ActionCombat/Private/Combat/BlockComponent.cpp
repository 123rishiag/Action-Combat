// Action Combat


#include "Combat/BlockComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "Animation/AnimMontage.h"

UBlockComponent::UBlockComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UBlockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

bool UBlockComponent::CheckBlock(AActor* Opponent)
{
	ACharacter* CharacterRef = GetOwner<ACharacter>();
	if (!CharacterRef->Implements<UMainPlayer>())
	{
		return true;
	}

	IMainPlayer* PlayerRef = Cast<IMainPlayer>(CharacterRef);

	FVector OpponentForward = Opponent->GetActorForwardVector();
	FVector PlayerForward = CharacterRef->GetActorForwardVector();

	double Result = FVector::DotProduct(OpponentForward, PlayerForward);

	if (Result > 0 || !PlayerRef->HasEnoughStamina(StaminaCost))
	{
		return true;
	}

	CharacterRef->PlayAnimMontage(BlockAnimMontage);

	OnBlockDelegate.Broadcast(StaminaCost);

	return false;
}

void UBlockComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

