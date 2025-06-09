// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "MainCharacter.generated.h"

class UPlayerAnimInstance;

class UStatsComponent;
class UPlayerActionsComponent;
class ULockonComponent;
class UCombatComponent;
class UBlockComponent;
class UTraceComponent;

UCLASS()
class ACTIONCOMBAT_API AMainCharacter : public ACharacter, public IMainPlayer
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UPlayerAnimInstance* PlayerAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStatsComponent* Stats;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPlayerActionsComponent* PlayerActions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	ULockonComponent* Lockon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCombatComponent* Combat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBlockComponent* Block;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTraceComponent* Trace;
};
