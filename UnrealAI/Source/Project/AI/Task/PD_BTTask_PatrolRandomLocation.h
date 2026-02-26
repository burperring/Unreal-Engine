
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "PD_BTTask_PatrolRandomLocation.generated.h"


UCLASS()
class PROJECT4_API UPD_BTTask_PatrolRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UPD_BTTask_PatrolRandomLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float SearchRadius = 1500.f;
};
