// Action Combat


#include "Characters/BossCharacter.h"
#include "Components/WidgetComponent.h"

#include "Characters/EStat.h"
#include "Characters/StatsComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	LockonWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockonWidget"));
	LockonWidget->SetupAttachment(RootComponent);
	LockonWidget->SetWidgetSpace(EWidgetSpace::Screen);
	LockonWidget->SetDrawSize(FVector2D(200, 200));
	LockonWidget->SetVisibility(false);

	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SightRadius = 3000.0f;
	PawnSensingComp->SetPeripheralVisionAngle(180.0f);

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

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	BlackBoardComp = GetController<AAIController>()->GetBlackboardComponent();

	BlackBoardComp->SetValueAsEnum(
		TEXT("CurrentState"),
		InitialState
	);
}

