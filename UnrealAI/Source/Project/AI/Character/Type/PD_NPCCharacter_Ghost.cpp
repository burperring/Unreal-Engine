

#include "PD_NPCCharacter_Ghost.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APD_NPCCharacter_Ghost::APD_NPCCharacter_Ghost()
{
	PrimaryActorTick.bCanEverTick = true;
	
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Capsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->SetMovementMode(MOVE_Flying);
	MovementComponent->GravityScale = 0.f;
	MovementComponent->MaxFlySpeed = 300.f;
	MovementComponent->MaxAcceleration = 5000.f;
	MovementComponent->bUseControllerDesiredRotation = true;
	MovementComponent->RotationRate = FRotator(0.f, 120.f, 0.f);
	
	RunningTime = 0.f;
}

void APD_NPCCharacter_Ghost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RunningTime += DeltaTime;
	
	const float ZOffset = FMath::Sin(RunningTime * HoverSpeed) * HoverAmplitude;
	AddActorWorldOffset(FVector(0.f, 0.f, ZOffset), false);
}
