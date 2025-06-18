// Action Combat


#include "Characters/BossCharacter.h"
#include "Components/WidgetComponent.h"

#include "Characters/EStat.h"
#include "Characters/StatsComponent.h"
#include "Combat/TraceComponent.h"
#include "Combat/CombatComponent.h"
#include "Combat/EnemyProjectileComponent.h"
#include "Characters/LookAtPlayerComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	LockonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockonWidget"));
	LockonWidget->SetupAttachment(RootComponent);
	LockonWidget->SetWidgetSpace(EWidgetSpace::Screen);
	LockonWidget->SetDrawSize(FVector2D(200, 200));
	LockonWidget->SetVisibility(false);

	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Trace = CreateDefaultSubobject<UTraceComponent>(TEXT("Trace"));
	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	EnemyProjectileComp = CreateDefaultSubobject<UEnemyProjectileComponent>(TEXT("EnemyProjectileComp"));
	LookAtPlayerComp = CreateDefaultSubobject<ULookAtPlayerComponent>(TEXT("LookAtPlayerComp"));

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SightRadius = 3000.0f;
	PawnSensingComp->SetPeripheralVisionAngle(180.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

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

void ABossCharacter::DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect)
{
	EEnemyState CurrentState = static_cast<EEnemyState>(BlackBoardComp->GetValueAsEnum(
		TEXT("CurrentState")
	));

	if (DetectedPawn != PawnToDetect && CurrentState != EEnemyState::IDLE) 
	{ 
		return; 
	}

	BlackBoardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		EEnemyState::RANGE
	);
}

float ABossCharacter::GetDamage()
{
	return Stats->Stats[EStat::Strength];
}

void ABossCharacter::Attack()
{
	Combat->RandomAttack();
}

float ABossCharacter::GetAnimDuration()
{
	return Combat->AnimDuration;
}

float ABossCharacter::GetMeleeRange()
{
	return Stats->Stats[EStat::MeleeRange];
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	BlackBoardComp = GetController<AAIController>()->GetBlackboardComponent();

	BlackBoardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState
	);
}

