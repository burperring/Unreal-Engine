
#pragma once

#include "CoreMinimal.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "PD_NPCCharacter_Scorch.generated.h"


class APD_EnemyProjectile;

UCLASS()
class PROJECT4_API APD_NPCCharacter_Scorch : public APD_NPCCharacter_Base
{
	GENERATED_BODY()

public:
	APD_NPCCharacter_Scorch();
	
	virtual void Attack() override;
	virtual void SpecialAttack() override;
	
	UFUNCTION(Server, Reliable)
	void ServerSpawnProjectile(APD_NPCCharacter_Base* SpawnActor);
	void ServerSpawnProjectile_Implementation(APD_NPCCharacter_Base* SpawnActor);
	UFUNCTION(NetMulticast, Reliable)
	void MultiSpawnProjectile(APD_NPCCharacter_Base* SpawnActor);
	void MultiSpawnProjectile_Implementation(APD_NPCCharacter_Base* SpawnActor);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* SpecialAttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Projectile", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APD_EnemyProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Projectile", meta = (AllowPrivateAccess = "true"))
	float LaunchSpeed = 1500.f;
};
