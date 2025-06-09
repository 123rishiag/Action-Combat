// Action Combat


#include "Characters/BossCharacter.h"
#include "Components/WidgetComponent.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	LockonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockonWidget"));
	LockonWidget->SetupAttachment(RootComponent);
	LockonWidget->SetWidgetSpace(EWidgetSpace::Screen);
	LockonWidget->SetDrawSize(FVector2D(200, 200));
	LockonWidget->SetVisibility(false);

}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABossCharacter::OnSelect_Implementation()
{
	if (IsValid(LockonWidget))
	{
		LockonWidget->SetVisibility(true);
	}
}

void ABossCharacter::OnDeselect_Implementation()
{
	if (IsValid(LockonWidget))
	{
		LockonWidget->SetVisibility(false);
	}
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

}

