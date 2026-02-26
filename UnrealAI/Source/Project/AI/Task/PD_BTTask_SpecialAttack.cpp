
#include "PD_BTTask_SpecialAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "Project4/AI/Pawn/PD_NPCPawn_Base.h"

UPD_BTTask_SpecialAttack::UPD_BTTask_SpecialAttack()
{
	NodeName = "NPC Special Attack";
}

EBTNodeResult::Type UPD_BTTask_SpecialAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const bool OutOfRange = OwnerComp.GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
	if (OutOfRange == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	
	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (APD_NPCCharacter_Base* const NPCCharacter = Cast<APD_NPCCharacter_Base>(AIController->GetPawn()))
		NPCCharacter->SpecialAttack();
	if (APD_NPCPawn_Base* const NPCPawn = Cast<APD_NPCPawn_Base>(AIController->GetPawn()))
		NPCPawn->SpecialAttack();
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
