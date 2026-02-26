// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PD_Scorch_Fire_AnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT4_API UPD_Scorch_Fire_AnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
