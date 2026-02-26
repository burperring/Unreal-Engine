
#include "PD_Scorch_Fire_AnimNotify.h"

#include "Project4/AI/Character/Type/PD_NPCCharacter_Scorch.h"

void UPD_Scorch_Fire_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* ActorCheck = MeshComp->GetOwner();

	if (ActorCheck) 
	{
		APD_NPCCharacter_Scorch* NPC = Cast<APD_NPCCharacter_Scorch>(ActorCheck);
		if (NPC)
		{
			NPC->ServerSpawnProjectile(NPC);
		}
	}
}
