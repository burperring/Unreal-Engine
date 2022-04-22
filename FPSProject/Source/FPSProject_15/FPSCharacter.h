// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/Camera/CameraComponent.h>
#include "FPSProjectile.h"
#include "FPSCharacter.generated.h"

UCLASS()
class FPSPROJECT_15_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float AxisValue);

	UFUNCTION()
		void MoveRight(float AxisValue);

	// ���� ��� ���� ī�޶� ȸ�����ó�� ���̽� Ŭ������ ������ ����Ǿ� �ִ�.
	// ĳ������ ������ Character ���̽� Ŭ������ bPressedJump ������ �����־ ����Ű�� ������ �� ������ true�� �����ϰ�,
	// ����Ű���� ���� ���� false�� �������ֱ⸸ �ϸ� �ȴ�.
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<AFPSProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
		USkeletalMeshComponent* FPSMesh;
};
