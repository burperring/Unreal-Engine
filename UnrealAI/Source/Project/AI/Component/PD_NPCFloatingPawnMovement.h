
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PD_NPCFloatingPawnMovement.generated.h"



UCLASS()
class PROJECT4_API UPD_NPCFloatingPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
protected:
	// 회전
	void RotateToMovementDirection(float DeltaTime);
	
	// 중력
	void ApplyGravity(float DeltaTime);
	bool IsNavMoving() const;						// 움직임 체크
	bool IsConsideredGrounded() const;				// 덜덜이 보정
	bool CheckGround(FHitResult& OutHit) const;		// 바닥 체크
	
private:
	// 회전
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement|Rotate", meta = (AllowPrivateAccess = "true"))
	float RotationInterpSpeed = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement|Rotate", meta = (AllowPrivateAccess = "true"))
	float MaxTurnSpeed = 360.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement|Rotate", meta = (AllowPrivateAccess = "true"))
	float TurnAcceleration = 720.f;
	
	float CurrentTurnSpeed = 0.f;
	
	// 중력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement|Gravity", meta = (AllowPrivateAccess = "true"))
	bool bIsUseGravity = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement|Gravity", meta = (AllowPrivateAccess = "true", EditCondition = "bIsUseGravity", EditConditionHides))
	float Gravity = -980.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement|Gravity", meta = (AllowPrivateAccess = "true", EditCondition = "bIsUseGravity", EditConditionHides))
	float MaxFallSpeed = -9800.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Movement|Gravity", meta = (AllowPrivateAccess = "true", EditCondition = "bIsUseGravity", EditConditionHides))
	float GroundCheckDistance = 10.f;

	float VelocityZ = 0.f;
	bool bIsGrounded = false;
};
