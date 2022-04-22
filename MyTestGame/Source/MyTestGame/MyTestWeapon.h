// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBasicCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyTestWeapon.generated.h"

UCLASS()
class MYTESTGAME_API AMyTestWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestWeapon(const class FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(AMyBasicCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const AMyTestWeapon* LastWeapon);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		class UBoxComponent* WeaponCollision;

protected:
	class AMyBasicCharacter* MyPawn;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;

	UPROPERTY(EditDefaultsOnly, Category = "MyFX")
		UParticleSystem* HitFX;
};
