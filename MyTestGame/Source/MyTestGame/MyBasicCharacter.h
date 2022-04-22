// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "MyBasicCharacter.generated.h"

UCLASS()
class MYTESTGAME_API AMyBasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBasicCharacter();

	USkeletalMeshComponent* GetSpesificPawnMesh()const;

	FName GetWeaponAttachPoint()const;

	void EquipWeapon(class AMyTestWeapon* Weapon);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float myHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float myMaxHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category=Inventory)
		FName WeaponAttachPoint;

	TArray<class AMyTestWeapon*>Inventory;

	class AMyTestWeapon* CurrentWeapon;

	void AddWeapon(class AMyTestWeapon* Weapon);

	void SetCurrentWeapon(class AMyTestWeapon* NewWeapon, class AMyTestWeapon* LastWeapon);

	void SpawnDefaultInventory();

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser);

	void DeathAnimationEnd();

	UPROPERTY(EditDefaultsOnly, Category=Inventory)
		TArray<TSubclassOf<class AMyTestWeapon>>DefaultInventoryClasses;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Attack_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Death_AnimMontage;

	void Attack_Melee();
	void Attack_Melee_End();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	bool isDuringAttack = true;
	int32 ComboAttack_Num;
};
