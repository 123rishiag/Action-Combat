// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Enemy.h"
#include "Components/WidgetComponent.h"
#include "BossCharacter.generated.h"

//class UWidgetComponent;

UCLASS()
class ACTIONCOMBAT_API ABossCharacter : public ACharacter, public IEnemy
{
	GENERATED_BODY()

public:
	ABossCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnSelect_Implementation() override;
	virtual void OnDeselect_Implementation() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* LockonWidget;
};
