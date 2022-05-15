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
	PrimaryActorTick.bStartWithTickEnabled = true;	// BeginPlay 함수가 동작한 직후에 Tick 함수가 동작하게 만들어 준다.

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// 캐릭터가 움직이더라도 카메라는 움직이지 않게 만드는 코드
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);	// 캐릭터가 움직일 방향과 보는 방향이 다를경우 초당 640도씩 회전하며 위치를 잡는다.
	GetCharacterMovement()->bConstrainToPlane = true;	// 캐릭터가 평면에서만 움직일 수 있도록 만들어 준다.
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true);	// 스프링 암의 회전이 루트 컴포넌트와 상위 컴포넌트를 따르지 않고 월드 좌표계의 회전을 따르도록 한다.
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;	// bDoCollisionTest는 카메라가 벽과 닿으면 충돌 계산을 통해 카메라와 캐릭터의 거리를 좁혀 카메라가 벽을 뚫지 못하게 만들어주는 프로퍼티
	
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

