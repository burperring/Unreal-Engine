
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PD_BTTask_NPCAttack.generated.h"


UCLASS()
class PROJECT4_API UPD_BTTask_NPCAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UPD_BTTask_NPCAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
