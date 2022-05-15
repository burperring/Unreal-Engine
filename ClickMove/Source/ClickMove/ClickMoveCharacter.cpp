// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMoveCharacter.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/Camera/CameraComponent.h>
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>
#include <Engine/Classes/GameFramework/SpringArmComponent.h>

// Sets default values
AClickMoveCharacter::AClickMoveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;	// BeginPlay �Լ��� ������ ���Ŀ� Tick �Լ��� �����ϰ� ����� �ش�.

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// ĳ���Ͱ� �����̴��� ī�޶�� �������� �ʰ� ����� �ڵ�
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);	// ĳ���Ͱ� ������ ����� ���� ������ �ٸ���� �ʴ� 640���� ȸ���ϸ� ��ġ�� ��´�.
	GetCharacterMovement()->bConstrainToPlane = true;	// ĳ���Ͱ� ��鿡���� ������ �� �ֵ��� ����� �ش�.
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true);	// ������ ���� ȸ���� ��Ʈ ������Ʈ�� ���� ������Ʈ�� ������ �ʰ� ���� ��ǥ���� ȸ���� �������� �Ѵ�.
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;	// bDoCollisionTest�� ī�޶� ���� ������ �浹 ����� ���� ī�޶�� ĳ������ �Ÿ��� ���� ī�޶� ���� ���� ���ϰ� ������ִ� ������Ƽ
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AClickMoveCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClickMoveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AClickMoveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

