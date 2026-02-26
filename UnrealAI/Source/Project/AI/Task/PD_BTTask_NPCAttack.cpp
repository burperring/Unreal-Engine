
#include "PD_BTTask_NPCAttack.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "Project4/AI/Controller/PD_AIController_Base.h"
#include "Project4/AI/Pawn/PD_NPCPawn_Base.h"

UPD_BTTask_NPCAttack::UPD_BTTask_NPCAttack()
{
	NodeName = "NPC Attack";
}

EBTNodeResult::Type UPD_BTTask_NPCAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const bool OutOfRange = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (APD_NPCCharacter_Base* const NPCCharacter = Cast<APD_NPCCharacter_Base>(AIController->GetPawn()))
		NPCCharacter->Attack();
	if (APD_NPCPawn_Base* const NPCPawn = Cast<APD_NPCPawn_Base>(AIController->GetPawn()))
		NPCPawn->Attack();
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
