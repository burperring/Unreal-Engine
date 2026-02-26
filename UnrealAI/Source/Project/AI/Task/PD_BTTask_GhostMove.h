
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PD_BTTask_GhostMove.generated.h"


UCLASS()
class PROJECT4_API UPD_BTTask_GhostMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UPD_BTTask_GhostMove();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category="Ghost")
	float MoveInputScale = 0.6f;
	UPROPERTY(EditAnywhere, Category="Ghost")
	float AcceptableRadius = 150.f;
};
