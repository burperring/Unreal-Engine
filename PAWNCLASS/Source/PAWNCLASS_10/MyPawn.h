// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

// Pawn class ����
// Pawn class�� �÷��̾ AI�� ��Ʈ�ѷ��� ����Ǿ� ������� �� �ֵ��� ����� Ŭ������ �ǹ��Ѵ�

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

	// USceneComponent�� ��ġ�� ȸ�� ���� Ʈ������ ������ ������ ������
	// ���忡 ��ġ ������ �ٸ� ������Ʈ���� �θ� Ŭ������ �Ǵ� ������Ʈ�̴�
	// �ű⿡ ���� �浹�� ���� ���� ȿ���� �������� �ʰ� ������ ����� ���� ������
	// ���� �������� ���� �������� ���̷� Ȱ���ϱ� ���� ������Ʈ�̴�
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
