
#pragma once

#include "CoreMinimal.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "PD_NPCCharacter_Nomal.generated.h"


UCLASS()
class PROJECT4_API APD_NPCCharacter_Nomal : public APD_NPCCharacter_Base
{
	GENERATED_BODY()
	
public:
	APD_NPCCharacter_Nomal();
	
	virtual void Attack() override;
	virtual void SpecialAttack() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* SpecialAttackMontage;
};
