// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MyTestGameAIController.generated.h"

/**
 * 
 */
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class MYTESTGAME_API AMyTestGameAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyTestGameAIController(FObjectInitializer const& object_intializer = FObjectInitializer::Get());

	virtual void BeginPlay()override;
	virtual void OnPossess(APawn* aPawn)override;
	virtual void Tick(float DeltaSeconds)override;
	virtual FRotator GetControlRotation()const override;

	UFUNCTION(BlueprintCallable, Category = Behavior)
		void on_target_detected(AActor* Actor, FAIStimulus const stimulus);

	class UBlackboardComponent* get_Blackboard() const;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* bTree;

	class UBlackboardComponent* blackboard;
	class UAISenseConfig_Sight* sight_config;

	void setup_perception_system();
};
