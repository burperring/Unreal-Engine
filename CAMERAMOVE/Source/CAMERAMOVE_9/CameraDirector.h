// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FChangeCameraData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeBetweenCameraChanges;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SmoothBlendTime;
};

UCLASS()
class CAMERAMOVE_9_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 언리얼 엔진에서 배열을 사용할 때는 C++에서 사용하는 []과 다르게 TArray 함수를 사용한다
	// 아래 함수처럼 TArray<AActor*>로 선언하면 AActor함수의 배열을 선언한다는 의미이다
	UPROPERTY(EditAnywhere)
		TArray<FChangeCameraData> Cameras;

	int32 NowCameraIndex;

	/*UPROPERTY(EditAnywhere)
		AActor* CameraOne;
	UPROPERTY(EditAnywhere)
		AActor* CameraTwo;*/
	UPROPERTY(EditAnywhere)
		float TimeToNextCameraChange;
};
