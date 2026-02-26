
#include "PD_BTService_PlayerInAttackRange.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "Project4/AI/Controller/PD_AIController_Base.h"

UPD_BTService_PlayerInAttackRange::UPD_BTService_PlayerInAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = "In Attack Range Check";
}

void UPD_BTService_PlayerInAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaTime);
	
	const APD_AIController_Base* AIController = Cast<APD_AIController_Base>(OwnerComp.GetAIOwner());
	const APD_NPCCharacter_Base* NPCCharacter = Cast<APD_NPCCharacter_Base>(AIController->GetPawn());
	if (NPCCharacter == nullptr) return;
	
	ACharacter* PlayerCharacter = Cast<ACharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	if (PlayerCharacter == nullptr) return;
	
	float CheckRange = bIsSpecialAttack ? NPCCharacter->GetSpecialAttackRange() : NPCCharacter->GetAttackRange();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), NPCCharacter->GetDistanceTo(PlayerCharacter) <= CheckRange);
}
