
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Project4/AI/Interface/PD_NPC_Combat_Interface.h"
#include "PD_NPCCharacter_Base.generated.h"

UCLASS()
class PROJECT4_API APD_NPCCharacter_Base : public ACharacter, public IPD_NPC_Combat_Interface
{
	GENERATED_BODY()

public:
	APD_NPCCharacter_Base();
	
	virtual void Attack() override;
	virtual void SpecialAttack() override;
	
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return Tree; }
	FORCEINLINE int32 GetAttackRange() const { return AttackRange; }
	FORCEINLINE int32 GetSpecialAttackRange() const { return SpecialAttackRange; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	float SpecialAttackRange = 500.f;
};
