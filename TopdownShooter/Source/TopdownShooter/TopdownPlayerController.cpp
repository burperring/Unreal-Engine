// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownPlayerController.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>

ATopdownPlayerController::ATopdownPlayerController()
{
	bShowMouseCursor = true;
}

void ATopdownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATopdownPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATopdownPlayerController::MoveRight);
}

void ATopdownPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	LookMouseCursor();
}

void ATopdownPlayerController::MoveForward(float AxisValue)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		FVector Direction = FVector::ForwardVector;
		MyPawn->AddMovementInput(Direction, AxisValue);
	}
}

void ATopdownPlayerController::MoveRight(float AxisValue)
{
	APawn* const MyPawn = GetPawn();

	if (MyPawn)
	{
		FVector Direction = FVector::RightVector;
		MyPawn->AddMovementInput(Direction, AxisValue);
	}
}

void ATopdownPlayerController::LookMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		APawn* const MyPawn = GetPawn();

		if (MyPawn)
		{
			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(MyPawn->GetActorLocation(),
				FVector(Hit.Location.X, Hit.Location.Y, MyPawn->GetActorLocation().Z));
			MyPawn->SetActorRotation(LookRotation);
		}
	}
}
