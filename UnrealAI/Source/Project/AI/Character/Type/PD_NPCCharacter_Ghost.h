
#pragma once

#include "CoreMinimal.h"
#include "Project4/AI/Character/PD_NPCCharacter_Base.h"
#include "PD_NPCCharacter_Ghost.generated.h"


UCLASS()
class PROJECT4_API APD_NPCCharacter_Ghost : public APD_NPCCharacter_Base
{
	GENERATED_BODY()
	
public:
	APD_NPCCharacter_Ghost();
	
	virtual void Tick(float DeltaTime) override;
	
private:
	float RunningTime = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Ghost|Hover", meta = (AllowPrivateAccess = "true"))
	float HoverSpeed = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Ghost|Hover", meta = (AllowPrivateAccess = "true"))
	float HoverAmplitude = .4f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Ghost|Movement", meta = (AllowPrivateAccess = "true"))
	float MoveInputScale = 1.f;
};
