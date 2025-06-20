// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Characters/EEnemyState.h"
#include "Components/WidgetComponent.h"
#include "Interfaces/Fighter.h"
#include "BossCharacter.generated.h"

class AAIController;
class UAnimMontage;

class UStatsComponent;
class UTraceComponent;
class UCombatComponent;
class UEnemyProjectileComponent;
class ULookAtPlayerComponent;
class UPawnSensingComponent;
class UBlackboardComponent;

UCLASS()
class ACTIONCOMBAT_API ABossCharacter : public ACharacter, public IEnemy, public IFighter
{
	GENERATED_BODY()

public:
	ABossCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnSelect_Implementation() override;
	virtual void OnDeselect_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void DetectPawn(APawn* DetectedPawn, APawn* PawnToDetect);

	virtual float GetDamage() override;

	virtual void Attack() override;

	virtual float GetAnimDuration() override;

	virtual float GetMeleeRange() override;

	UFUNCTION()
	void HandlePlayerDeath();

	UFUNCTION(BlueprintCallable)
	void HandleDeath();

	UFUNCTION()
	void FinishDeathAnim();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* LockonWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStatsComponent* Stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTraceComponent* Trace;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCombatComponent* Combat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEnemyProjectileComponent* EnemyProjectileComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	ULookAtPlayerComponent* LookAtPlayerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UPawnSensingComponent* PawnSensingComp;

private:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EEnemyState> InitialState;

	UBlackboardComponent* BlackBoardComp;

	UPROPERTY(EditAnywhere)
	UAnimMontage* DeathAnimMontage;

	AAIController* ControllerRef;

};
