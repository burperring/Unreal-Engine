
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Pawn.h"
#include "Project4/AI/Interface/PD_NPC_Combat_Interface.h"
#include "PD_NPCPawn_Base.generated.h"


class USkeletalMeshComponent;
class UCapsuleComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UPD_NPCFloatingPawnMovement;

UCLASS()
class PROJECT4_API APD_NPCPawn_Base : public APawn, public IPD_NPC_Combat_Interface
{
	GENERATED_BODY()

public:
	APD_NPCPawn_Base();
	
	virtual void Attack() override;
	virtual void SpecialAttack() override;
	
	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return Tree; }
	FORCEINLINE int32 GetAttackRange() const { return AttackRange; }
	FORCEINLINE int32 GetSpecialAttackRange() const { return SpecialAttackRange; }
	FORCEINLINE UPD_NPCFloatingPawnMovement* GetMovement() const { return MovementComponent; }

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> ArrowComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPD_NPCFloatingPawnMovement> MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Attack", meta = (AllowPrivateAccess = "true"))
	float SpecialAttackRange = 500.f;
};
