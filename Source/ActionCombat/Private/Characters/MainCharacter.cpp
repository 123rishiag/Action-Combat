// Action Combat


#include "Characters/MainCharacter.h"
#include "Animations/PlayerAnimInstance.h"

#include "Characters/EStat.h"
#include "Characters/StatsComponent.h"
#include "Characters/PlayerActionsComponent.h"
#include "Combat/LockonComponent.h"
#include "Combat/CombatComponent.h"
#include "Combat/BlockComponent.h"
#include "Combat/TraceComponent.h"

AMainCharacter::AMainCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	PlayerActions = CreateDefaultSubobject<UPlayerActionsComponent>(TEXT("PlayerActions"));
	Lockon = CreateDefaultSubobject<ULockonComponent>(TEXT("Lockon"));
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	Block = CreateDefaultSubobject<UBlockComponent>(TEXT("Block"));
	Trace = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace"));

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMainCharacter::GetDamage()
{
	return Stats->Stats[EStat::Strength];
}

bool AMainCharacter::HasEnoughStamina(float Cost)
{
	return Stats->Stats[EStat::Stamina] >= Cost;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

}
