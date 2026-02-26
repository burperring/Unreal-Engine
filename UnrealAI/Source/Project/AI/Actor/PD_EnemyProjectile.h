
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PD_EnemyProjectile.generated.h"


class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class PROJECT4_API APD_EnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	APD_EnemyProjectile();
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(NetMulticast, Reliable)
	void MultiDestroyProjectile();
	void MultiDestroyProjectile_Implementation();
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TObjectPtr<USceneComponent> SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TObjectPtr<USphereComponent> SphereComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	FTimerHandle DestroyProjectileHandle;
};
