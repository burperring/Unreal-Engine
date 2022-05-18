// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TopdownPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API ATopdownPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATopdownPlayerController();

	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION()
		void MoveForward(float AxisValue);

	UFUNCTION()
		void MoveRight(float AxisValue);

	UFUNCTION()
		void LookMouseCursor();
};
