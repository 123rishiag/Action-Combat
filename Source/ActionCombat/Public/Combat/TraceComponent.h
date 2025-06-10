// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"

class USkeletalMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONCOMBAT_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTraceComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	bool bIsAttacking = false;

	UFUNCTION(BlueprintCallable)
	void HandleResetAttack();

protected:
	virtual void BeginPlay() override;

private:
	USkeletalMeshComponent* SkeletalComp;

	UPROPERTY(EditAnywhere)
	FName Start;

	UPROPERTY(EditAnywhere)
	FName End;

	UPROPERTY(EditAnywhere)
	FName Rotation;

	UPROPERTY(EditAnywhere)
	double BoxCollisionLength = 30.0;

	UPROPERTY(EditAnywhere)
	bool bDebugMode = false;

	TArray<AActor*> TargetsToIgnore;

};
