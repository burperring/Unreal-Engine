
#include "PD_NPCFloatingPawnMovement.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Navigation/PathFollowingComponent.h"


void UPD_NPCFloatingPawnMovement::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	if (!PawnOwner || !UpdatedComponent) return;
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ApplyGravity(DeltaTime);
	RotateToMovementDirection(DeltaTime);
}

void UPD_NPCFloatingPawnMovement::RotateToMovementDirection(float DeltaTime)
{
	FVector PawnVelocity = Velocity;
	PawnVelocity.Z = 0.f;

	if (PawnVelocity.SizeSquared() < 5.f)
	{
		CurrentTurnSpeed = FMath::FInterpTo(CurrentTurnSpeed, 0.f, DeltaTime, 5.f);
		return;
	}
	
	FRotator CurrentRot = PawnOwner->GetActorRotation();
	FRotator TargetRot = PawnVelocity.Rotation();
	float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentRot.Yaw, TargetRot.Yaw);
	
	float TargetTurnSpeed = FMath::Clamp(
		FMath::Abs(DeltaYaw) * RotationInterpSpeed,  // 각도 클수록 빠르게
		180.f,
		MaxTurnSpeed
	);
	
	CurrentTurnSpeed = FMath::FInterpConstantTo(
		CurrentTurnSpeed,
		TargetTurnSpeed,
		DeltaTime,
		TurnAcceleration
	);
	
	float YawStep = FMath::Clamp(
		DeltaYaw,
		-CurrentTurnSpeed * DeltaTime,
		 CurrentTurnSpeed * DeltaTime
	);

	PawnOwner->SetActorRotation(FRotator(0.f, CurrentRot.Yaw + YawStep, 0.f));
}

void UPD_NPCFloatingPawnMovement::ApplyGravity(float DeltaTime)
{
	if (!bIsUseGravity) return;
	
	Velocity = FVector(Velocity.X, Velocity.Y, 0.f);
	bIsGrounded = IsConsideredGrounded();
	
	if (bIsGrounded && VelocityZ <= 0.f)
	{
		VelocityZ = 0.f;
	}
	else
	{
		VelocityZ += Gravity * DeltaTime;
		VelocityZ = FMath::Max(VelocityZ, MaxFallSpeed);
		
		FVector Delta = FVector(0.f, 0.f, VelocityZ) * DeltaTime;
		FHitResult Hit;
		SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}

bool UPD_NPCFloatingPawnMovement::IsNavMoving() const
{
	const AAIController* AI = Cast<AAIController>(PawnOwner->GetController());
	if (AI == nullptr) return false;

	const UPathFollowingComponent* PathComp = AI->GetPathFollowingComponent();
	return PathComp && PathComp->GetStatus() == EPathFollowingStatus::Moving;
}

bool UPD_NPCFloatingPawnMovement::IsConsideredGrounded() const
{
	FHitResult GroundHit;
	const bool bHitGround = CheckGround(GroundHit);
	if (bHitGround) return true;
	
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(UpdatedComponent);
	if (Capsule == nullptr) return false;
	
	if (IsNavMoving())
	{
		const float ZDiff = PawnOwner->GetActorLocation().Z - Capsule->GetScaledCapsuleHalfHeight();
		UE_LOG(LogTemp, Warning, TEXT("bHitGround: %f"), ZDiff);
		if (ZDiff < 5.f)
			return true;
	}

	return false;
}

bool UPD_NPCFloatingPawnMovement::CheckGround(FHitResult& OutHit) const
{
	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(UpdatedComponent);
	if (Capsule == nullptr) return false;
	
	const float Radius = Capsule->GetScaledCapsuleRadius();
	const float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();
	
	const FVector Start = Capsule->GetComponentLocation();
	const FVector End = Start - FVector(0.f, 0.f, GroundCheckDistance);
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(PawnOwner);
	
	return GetWorld()->SweepSingleByChannel(
		OutHit,
		Start,
		End,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(
			Radius,
			HalfHeight
		),
		CollisionParams
	);
}
