// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MyTestGameAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "MyBasicCharacter.h"
#include "MyTestGameBot.h"
#include "CombatInterface.h"

UBTTask_Attack::UBTTask_Attack(FObjectInitializer const& object_initiallizer)
{
	NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AAIController* const cont = owner_comp.GetAIOwner();
	AMyTestGameBot* const npcBot = Cast<AMyTestGameBot>(cont->GetPawn());
	if (ICombatInterface* const icombat = Cast<ICombatInterface>(npcBot))
	{
		if (montage_has_finished(npcBot))
		{
			icombat->Execute_melee_attack(npcBot);
		}
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UBTTask_Attack::montage_has_finished(AMyTestGameBot* const npcBot)
{
	return npcBot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcBot->get_montage());
}
