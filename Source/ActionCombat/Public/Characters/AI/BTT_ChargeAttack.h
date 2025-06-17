// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ChargeAttack.generated.h"


class AAIController;
class ACharacter;
class UBossAnimInstance;

/**
 * 
 */
UCLASS()
class ACTIONCOMBAT_API UBTT_ChargeAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_ChargeAttack();
	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;

	void ChargeAtPlayer();

	UFUNCTION()
	void HandleMoveCompleted();

	UFUNCTION()
	void FinishAttackTask();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	AAIController* ControllerRef;
	ACharacter* CharacterRef;
	UBossAnimInstance* BossAnim;

	UPROPERTY(EditAnywhere)
	float AcceptableRadius = 100.f;

	FScriptDelegate MoveCompletedDelegate;

	float OriginalWalkSpeed;

	UPROPERTY(EditAnywhere)
	float ChargeWalkSpeed = 2000.f;

	bool bIsFinished = false;

};
