
#include "PD_BTTask_ClearBBKeyValue.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Project4/AI/Controller/PD_AIController_Base.h"

UPD_BTTask_ClearBBKeyValue::UPD_BTTask_ClearBBKeyValue()
{
	NodeName = "Clear Value";
}

EBTNodeResult::Type UPD_BTTask_ClearBBKeyValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APD_AIController_Base* AIController = Cast<APD_AIController_Base>(OwnerComp.GetAIOwner());
	if (AIController == nullptr) return EBTNodeResult::Failed;
	
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	AIController->GetAIPerceptionComp()->ForgetAll();
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
