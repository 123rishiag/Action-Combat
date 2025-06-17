// Action Combat

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UParticleSystem;
class UProjectileMovementComponent;


UCLASS()
class ACTIONCOMBAT_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyProjectile();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HandleBeginOverlap(AActor* OtherActor);

	UFUNCTION()
	void DestroyProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ProjectileTemplate;

	UPROPERTY(EditAnywhere)
	UParticleSystem* HitTemplate;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;
};
