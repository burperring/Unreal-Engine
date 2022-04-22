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

	// �𸮾� �������� �迭�� ����� ���� C++���� ����ϴ� []�� �ٸ��� TArray �Լ��� ����Ѵ�
	// �Ʒ� �Լ�ó�� TArray<AActor*>�� �����ϸ� AActor�Լ��� �迭�� �����Ѵٴ� �ǹ��̴�
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
