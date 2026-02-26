
#include "PD_AIController_Base.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "Project4/AI/Pawn/PD_NPCPawn_Base.h"

APD_AIController_Base::APD_AIController_Base(const FObjectInitializer& OI) : Super(OI)
{
	bStartAILogicOnPossess = true;
	
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	HearingSense = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	DamageSense = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));
	
	AIPerceptionComp->OnPerceptionUpdated.AddDynamic(this, &APD_AIController_Base::PerceptionUpdated);
	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &APD_AIController_Base::TargetPerceptionUpdated);
	
	SetPerceptionComponent(*AIPerceptionComp);
}

void APD_AIController_Base::StartLogicAI() const
{
	if (BrainComponent)
	{
		BrainComponent->StartLogic();
	}
}

void APD_AIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	SetupPerceptionSystem();
	
	UBehaviorTree* BTTree {};
	
	if (const APD_NPCCharacter_Base* NPCCharacter = Cast<APD_NPCCharacter_Base>(InPawn))
		BTTree = NPCCharacter->GetBehaviorTree();
	else if (const APD_NPCPawn_Base* NPCPawn = Cast<APD_NPCPawn_Base>(InPawn))
		BTTree = NPCPawn->GetBehaviorTree();
	
	if (BTTree != nullptr)
	{
		UBlackboardComponent* BB;
		UseBlackboard(BTTree->BlackboardAsset, BB);
		Blackboard = BB;
		RunBehaviorTree(BTTree);
	}
	
	AIPerceptionComp->RequestStimuliListenerUpdate();
}

void APD_AIController_Base::SetupPerceptionSystem()
{
	if (SightSense)
	{
		SightSense->SightRadius = 600.f;
		SightSense->LoseSightRadius = 900.f;
		SightSense->PeripheralVisionAngleDegrees = 60.f;
		SightSense->SetMaxAge(1.f);
		SightSense->AutoSuccessRangeFromLastSeenLocation = -1.f;
		SightSense->DetectionByAffiliation.bDetectEnemies = true;
		SightSense->DetectionByAffiliation.bDetectFriendlies = true;
		SightSense->DetectionByAffiliation.bDetectNeutrals = true;
		
		AIPerceptionComp->ConfigureSense(*SightSense);
		AIPerceptionComp->SetDominantSense(SightSense->GetSenseImplementation());
	}
	if (HearingSense)
	{
		HearingSense->HearingRange = 1200.f;
		HearingSense->SetMaxAge(15.f);
		HearingSense->DetectionByAffiliation.bDetectEnemies = true;
		HearingSense->DetectionByAffiliation.bDetectFriendlies = true;
		HearingSense->DetectionByAffiliation.bDetectNeutrals = true;
		
		AIPerceptionComp->ConfigureSense(*HearingSense);
	}
	if (DamageSense)
	{
		DamageSense->SetMaxAge(15.f);
		HearingSense->DetectionByAffiliation.bDetectEnemies = true;
		HearingSense->DetectionByAffiliation.bDetectFriendlies = true;
		HearingSense->DetectionByAffiliation.bDetectNeutrals = true;
		
		AIPerceptionComp->ConfigureSense(*DamageSense);
	}
}

void APD_AIController_Base::PerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	for (AActor* UpdatedActor : UpdatedActors)
	{
		FAIStimulus AIStimulus;
		if (CanSenseActor(UpdatedActor, EAISense::AS_Sight, AIStimulus))		 HandleSenseSight(UpdatedActor);
		if (CanSenseActor(UpdatedActor, EAISense::AS_Hearing, AIStimulus))	 HandleSenseHearing(AIStimulus.StimulusLocation);
		if (CanSenseActor(UpdatedActor, EAISense::AS_Damage, AIStimulus))	 HandleSenseDamage(UpdatedActor);
	}
}

void APD_AIController_Base::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);
	
	if (SenseClass == UAISense_Sight::StaticClass())
	{
		if (!Stimulus.WasSuccessfullySensed() && Actor == TargetActor)
		{
			GetWorld()->GetTimerManager().SetTimer(
				SightTimer,
				this,
				&APD_AIController_Base::ClearSenseSight,
				5.f,
				false
			);
		}
		else
		{
			if (TargetActor == Actor)
				GetWorld()->GetTimerManager().ClearTimer(SightTimer);
		}
	}
	if (SenseClass == UAISense_Hearing::StaticClass())
	{
		if (!Stimulus.WasSuccessfullySensed())
		{
			ClearSenseHearing();
		}
	}
	if (SenseClass == UAISense_Damage::StaticClass())
	{
		if (!Stimulus.WasSuccessfullySensed())
		{
			ClearSenseDamage();
		}
	}
}

bool APD_AIController_Base::CanSenseActor(AActor* Actor, EAISense Sense, FAIStimulus& Stimulus)
{
	FActorPerceptionBlueprintInfo ActorPerceptionInfo;
	if (GetPerceptionComponent()->GetActorsPerception(Actor, ActorPerceptionInfo))
	{
		for (FAIStimulus& CurrentStimulus : ActorPerceptionInfo.LastSensedStimuli)
		{
			TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), CurrentStimulus);
			bool SenseMatched = false;
			
			switch (Sense)
			{
			case EAISense::AS_None:
				break;
			case EAISense::AS_Sight:
				if (SenseClass == UAISense_Sight::StaticClass())
				{
					SenseMatched = true;
				}
				break;
			case EAISense::AS_Hearing:
				if (SenseClass == UAISense_Hearing::StaticClass())
				{
					SenseMatched = true;
				}
				break;
			case EAISense::AS_Damage:
				if (SenseClass == UAISense_Damage::StaticClass())
				{
					SenseMatched = true;
				}
				break;
			default: break;
			}
			
			if (SenseMatched)
			{
				Stimulus = CurrentStimulus;
				return CurrentStimulus.WasSuccessfullySensed();
			}
		}
	}
	
	return false;
}

void APD_AIController_Base::HandleSenseSight(AActor* Actor)
{
	if (!IsValid(GetBlackboardComponent())) return;
	
	if (auto* const character = Cast<ACharacter>(Actor))
	{
		if (character->GetController()->IsPlayerController())
		{
			TargetActor = character;
			GetBlackboardComponent()->SetValueAsObject("TargetActor", character);
		}
	}
}

void APD_AIController_Base::ClearSenseSight()
{
	if (!IsValid(GetBlackboardComponent())) return;
	
	TargetActor = nullptr;
	GetBlackboardComponent()->ClearValue("TargetActor");
}

void APD_AIController_Base::HandleSenseHearing(FVector Location)
{
	if (!IsValid(GetBlackboardComponent())) return;
	
	LastLocation = Location;
	GetBlackboardComponent()->SetValueAsVector("TargetLocation", LastLocation);
}

void APD_AIController_Base::ClearSenseHearing()
{
	if (!IsValid(GetBlackboardComponent())) return;
	
	LastLocation = FVector::ZeroVector;
	GetBlackboardComponent()->ClearValue("TargetLocation");
}

void APD_AIController_Base::HandleSenseDamage(AActor* Actor)
{
	if (!IsValid(GetBlackboardComponent())) return;
	
	if (auto* const character = Cast<ACharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsObject("DamagedActor", character);
	}
}

void APD_AIController_Base::ClearSenseDamage()
{
	if (!IsValid(GetBlackboardComponent())) return;
	
	GetBlackboardComponent()->ClearValue("DamagedActor");
}

