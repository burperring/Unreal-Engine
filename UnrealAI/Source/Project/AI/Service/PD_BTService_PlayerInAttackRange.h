
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "PD_BTService_PlayerInAttackRange.generated.h"


UCLASS()
class PROJECT4_API UPD_BTService_PlayerInAttackRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UPD_BTService_PlayerInAttackRange();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bIsSpecialAttack;
};
