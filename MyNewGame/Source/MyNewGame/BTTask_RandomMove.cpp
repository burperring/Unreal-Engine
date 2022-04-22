// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomMove.h"
#include "MyNewGame.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "MyBotAIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "blackboard_keys.h"

UBTTask_RandomMove::UBTTask_RandomMove(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTTask_RandomMove::ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory)
{
	auto const cont = Cast<AMyBotAIController>(owner_Comp.GetAIOwner());
	auto const npc = cont->GetPawn();

	FVector const origin = npc->GetActorLocation();
	FNavLocation loc;

	UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav_sys->GetRandomPointInNavigableRadius(origin, search_radius, loc, nullptr))
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
	}

	FinishLatentTask(owner_Comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}
