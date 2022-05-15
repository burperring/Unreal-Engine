// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMovePlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

AClickMovePlayerController::AClickMovePlayerController()
{
	// ���콺 Ŀ�� ���̰� �ϱ�
	bShowMouseCursor = true;
}

void AClickMovePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// BindAction �Լ��� LeftClick �Է� ���ΰ� �Լ����� ���ε����ش�.
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &AClickMovePlayerController::InputLeftMouseButtonPressed);
	InputComponent->BindAction("LeftClick", IE_Released, this, &AClickMovePlayerController::InputLeftMouseButtonReleased);
}

void AClickMovePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bClickLeftMouse)
	{
		MoveToMouseCursor();
	}
}

void AClickMovePlayerController::InputLeftMouseButtonPressed()
{
	bClickLeftMouse = true;
}

void AClickMovePlayerController::InputLeftMouseButtonReleased()
{
	bClickLeftMouse = false;
}

void AClickMovePlayerController::SetNewDestination(const FVector Destination)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());
		if (Distance > 120.0f)
		{
			// Build.cs�� AIModule�� �����������ν� �����ϰ� ĳ���Ͱ� ������ �� �ִ� �ڵ带 ������ �� ����.
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
		}
	}
}

void AClickMovePlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetNewDestination(Hit.ImpactPoint);
	}
}
