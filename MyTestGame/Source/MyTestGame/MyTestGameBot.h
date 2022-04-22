// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasicCharacter.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "MyTestGameBot.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTGAME_API AMyTestGameBot : public AMyBasicCharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AMyTestGameBot();

	UPROPERTY(EditAnywhere, Category = Behavior)
		class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnywhere, Category = Behavior)
		UAnimMontage* Attack_Melee;

	virtual int melee_attack_Implementation()override;

	UAnimMontage* get_montage() const;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;
};
