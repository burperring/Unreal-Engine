// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMovePlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

AClickMovePlayerController::AClickMovePlayerController()
{
	// 마우스 커서 보이게 하기
	bShowMouseCursor = true;
}

void AClickMovePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// BindAction 함수로 LeftClick 입력 매핑과 함수들을 바인딩해준다.
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
			// Build.cs에 AIModule을 선언해줌으로써 간편하게 캐릭터가 움직일 수 있는 코드를 선언할 수 있음.
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
