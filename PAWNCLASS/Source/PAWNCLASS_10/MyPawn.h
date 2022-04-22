// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

// Pawn class 생성
// Pawn class는 플레이어나 AI의 컨트롤러가 연결되어 제어받을 수 있도록 설계된 클래스를 의미한다

UCLASS()
class PAWNCLASS_10_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// USceneComponent는 위치와 회전 같은 트랜스폼 정보를 가지고 있으며
	// 월드에 배치 가능한 다른 컴포넌트들의 부모 클래스가 되는 컴포넌트이다
	// 거기에 더해 충돌과 같은 물리 효과를 지원하지 않고 렌더링 기능이 없기 때문에
	// 아주 가벼워서 계층 구조에서 더미로 활용하기 좋은 컴포넌트이다
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void StartGrowing();
	void StopGrowing();

	FVector CurrentVelocity;
	bool bGrowing;

	float InputTime;
};
