
#include "PD_NPCCharacter_Nomal.h"

APD_NPCCharacter_Nomal::APD_NPCCharacter_Nomal()
{
}

void APD_NPCCharacter_Nomal::Attack()
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

void APD_NPCCharacter_Nomal::SpecialAttack()
{
	Super::SpecialAttack();
	
	USkeletalMeshComponent* MeshComp = GetMesh();
	if (MeshComp == nullptr) return;
	
	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (AnimInstance && SpecialAttackMontage)
	{
		if (!AnimInstance->IsAnyMontagePlaying())
			AnimInstance->Montage_Play(SpecialAttackMontage);
	}
}
