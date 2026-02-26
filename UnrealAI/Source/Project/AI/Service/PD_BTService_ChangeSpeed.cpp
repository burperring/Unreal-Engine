
#include "PD_BTService_ChangeSpeed.h"

#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "Project4/AI/Component/PD_NPCFloatingPawnMovement.h"
#include "Project4/AI/Pawn/PD_NPCPawn_Base.h"

UPD_BTService_ChangeSpeed::UPD_BTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Change Speed";
}

void UPD_BTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	if (auto const AIController = OwnerComp.GetAIOwner())
	{
		if (APD_NPCCharacter_Base* NPCCharacter = Cast<APD_NPCCharacter_Base>(AIController->GetPawn()))
		{
			NPCCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed;
		}
		if (APD_NPCPawn_Base* NPCPawn = Cast<APD_NPCPawn_Base>(AIController->GetPawn()))
		{
			NPCPawn->GetMovement()->MaxSpeed = Speed;
		}
	}
}
