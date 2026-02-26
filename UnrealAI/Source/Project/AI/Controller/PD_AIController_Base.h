
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "PD_AIController_Base.generated.h"


class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;
class UBehaviorTreeComponent;
class UAIPerceptionComponent;

UENUM()
enum class EAISense : uint8
{
	AS_None		UMETA(DisplayName = "None"),
	AS_Sight	UMETA(DisplayName = "Sight"),
	AS_Hearing	UMETA(DisplayName = "Hearing"),
	AS_Damage	UMETA(DisplayName = "Damage"),
	
	AS_Max		UMETA(DisplayName = "Max"),
};

UCLASS()
class PROJECT4_API APD_AIController_Base : public AAIController
{
	GENERATED_BODY()
	
public:
	explicit APD_AIController_Base(const FObjectInitializer& OI);
	void StartLogicAI() const;
	
	FORCEINLINE UAIPerceptionComponent* GetAIPerceptionComp() const { return AIPerceptionComp; }
	FORCEINLINE AActor* GetTargetActor() const { return TargetActor; }
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	UFUNCTION()
	virtual void SetupPerceptionSystem();
	UFUNCTION()
	void PerceptionUpdated(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
	bool CanSenseActor(AActor* Actor, EAISense Sense, FAIStimulus& Stimulus);
	void HandleSenseSight(AActor* Actor);
	void ClearSenseSight();
	void HandleSenseHearing(FVector Location);
	void ClearSenseHearing();
	void HandleSenseDamage(AActor* Actor);
	void ClearSenseDamage();
	
private:
	TObjectPtr<UAISenseConfig_Sight> SightSense;
	TObjectPtr<UAISenseConfig_Hearing> HearingSense;
	TObjectPtr<UAISenseConfig_Damage> DamageSense;
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComp;
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;
	
	TObjectPtr<AActor> TargetActor {};
	FVector LastLocation = FVector::ZeroVector;
	
	FTimerHandle SightTimer;
};
