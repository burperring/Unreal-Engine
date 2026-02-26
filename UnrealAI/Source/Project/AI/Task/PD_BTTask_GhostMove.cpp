
#include "PD_BTTask_GhostMove.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project4/AI/Character/Type/PD_NPCCharacter_Ghost.h"

UPD_BTTask_GhostMove::UPD_BTTask_GhostMove()
{
	bNotifyTick = true;
	NodeName = _T("GhostMove");
}

EBTNodeResult::Type UPD_BTTask_GhostMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UPD_BTTask_GhostMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	APD_NPCCharacter_Ghost* Ghost = Cast<APD_NPCCharacter_Ghost>(AIController->GetPawn());
	if (Ghost == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (BB == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	FVector TargetLocation = FVector::ZeroVector;
	if (const AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(GetSelectedBlackboardKey())))
		TargetLocation = TargetActor->GetActorLocation();
	else if (BB->IsVectorValueSet(GetSelectedBlackboardKey()))
		TargetLocation = BB->GetValueAsVector(GetSelectedBlackboardKey());
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	const FVector NPCLocation = Ghost->GetActorLocation();
	const float Distance = FVector::Dist(NPCLocation, TargetLocation);
	
	if (Distance <= AcceptableRadius)	// 일정 범위 도달 시 종료
	{
		Ghost->GetCharacterMovement()->StopMovementImmediately();
		Ghost->AddMovementInput(FVector::ZeroVector);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	
	FVector Direction = TargetLocation - NPCLocation;
	Direction.Z = 0.f;
	Direction.Normalize();

	Ghost->AddMovementInput(Direction, MoveInputScale);
}
