
#include "PD_NPCCharacter_Scorch.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project4/AI/Actor/PD_EnemyProjectile.h"
#include "Project4/AI/Controller/PD_AIController_Base.h"

APD_NPCCharacter_Scorch::APD_NPCCharacter_Scorch()
{
}

void APD_NPCCharacter_Scorch::Attack()
{
	Super::Attack();
	
	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp == nullptr) return;
	
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		if (!AnimInstance->IsAnyMontagePlaying())
			AnimInstance->Montage_Play(AttackMontage);
	}
}

void APD_NPCCharacter_Scorch::SpecialAttack()
{
	Super::SpecialAttack();
	
	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp == nullptr) return;
	
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (AnimInstance && SpecialAttackMontage)
	{
		AnimInstance->StopAllMontages(0.f);
		
		AnimInstance->Montage_Play(SpecialAttackMontage);
	}
}

void APD_NPCCharacter_Scorch::ServerSpawnProjectile_Implementation(APD_NPCCharacter_Base* SpawnActor)
{
	MultiSpawnProjectile(SpawnActor);
}

void APD_NPCCharacter_Scorch::MultiSpawnProjectile_Implementation(APD_NPCCharacter_Base* SpawnActor)
{
	if (!ProjectileClass) return;
	
	APD_AIController_Base* AIController = Cast<APD_AIController_Base>(GetController());
	if (AIController == nullptr) return;
	
	FVector StartLocation = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	FVector TargetLocation = AIController->GetTargetActor()->GetActorLocation() + AIController->GetTargetActor()->GetVelocity() * 0.3f;
	
	FVector LaunchVelocity;
	bool bHasSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		TargetLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (!bHasSolution) return;

	FActorSpawnParameters Params;
	Params.Owner = this;

	APD_EnemyProjectile* Projectile = GetWorld()->SpawnActor<APD_EnemyProjectile>(
		ProjectileClass,
		StartLocation,
		FRotator::ZeroRotator,
		Params
	);

	if (Projectile)
	{
		Projectile->FindComponentByClass<UProjectileMovementComponent>()
			->Velocity = LaunchVelocity;
	}
}
