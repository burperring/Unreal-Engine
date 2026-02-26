
#include "PD_BTTask_PatrolRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Project4/AI/Controller/PD_AIController_Base.h"

UPD_BTTask_PatrolRandomLocation::UPD_BTTask_PatrolRandomLocation()
{
	NodeName = "Patrol Random Location";
}

EBTNodeResult::Type UPD_BTTask_PatrolRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APD_AIController_Base* AIController = Cast<APD_AIController_Base>(OwnerComp.GetAIOwner());
	if (AIController == nullptr) return EBTNodeResult::Failed;

	if (auto const NPC = AIController->GetPawn())
	{
		FVector Location = NPC->GetActorLocation();
		
		if (auto NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			FNavLocation NavLocation;
			if (NavSys->GetRandomPointInNavigableRadius(Location, SearchRadius, NavLocation))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
			}
			
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
