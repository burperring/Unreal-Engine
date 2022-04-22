// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
// GetCapsuleComponent() �Լ��� ������ �ذ��ϱ� ���� �������
#include <Engine/Classes/Components/CapsuleComponent.h>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��� ���Ͽ��� ������ UCameraComponent�� ������ �Լ��� �����ؼ� ī�޶��� ��ġ�� �� ��ġ���� ��¦ ���� ������ ���
	// ���� ī�޶� �����̼��� �����ϵ��� �ڵ带 �ۼ��Ѵ�.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0 + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 1��Ī ���̷�Ż Mesh ������Ʈ �����ϰ� �����ִ� �ش� Mesh�� �� �� �ְ� �����.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);			// �ڱ� �ڽſ��Ը� �ش� Mesh�� ���̰� �������ְ� ī�޶� ���δ�.
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;	// �ش� Mesh�� �׸��ڰ� ������ �ʰ� �����.
	FPSMesh->CastShadow = false;

	// 3��Ī Mesh�� �ҷ��ͼ� �����ִ� �ش� Mesh�� �� �� ���� �����.
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// GameMode���� Ȯ���ϴ� �� ó�� FPSCharacter�� ���� ���Ǵ��� Ȯ���ϱ� ���� �α׸� ����ش�.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter!"));
	}
	// ���������� ���� ���� �𸮾� ������ ���ư��� FPSCharacter����� �������Ʈ�� �������ش�.
	// ���� ���� ���� -> ������Ʈ ���� -> ��&��� -> ���õ� GameMode�� ���� Default Pawn Class�� ã�� BP_FPSCharacter�� �������ش�.
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// �Լ� ������ ������ �����ӿ� �ش� �Լ����� ���ε� �����ش�.
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// ���콺 �����¿� �������� ��� �⺻������ �����Ǵ� ���� �����ϱ� ������ ���Ӱ� �Լ��� ������ �ʿ䰡 ����.
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);		// X�� ������
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);	// Y�� ������

	// ���� �Լ��� ���� ������ ���ε� ���ش�.
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	// �߻翡 ���õ� �Լ� ���ε�
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

// FPS���� ĳ������ �������� �����ϱ� ���ؼ��� ī�޶��� ���⿡ ���� �������� �����ؾ� �Ѵ�.
// "����"�� "ī�޶� ���ϴ� ����"�� �ǹ��ϰ� "����"�� "ī�޶� ���ϴ� ������ ����"�� �ǹ��Ѵ�.
// ĳ������ ���� ������ ���ϴ� ���� PlayerController�� ����Ѵ�.
// ���� MoveForward �Լ������� ���� ȸ���� ��ġ ������Ʈ�� �����ϰ� �Է��� XY ������ ���ѽ���
// ���� �Ʒ��� ó�ٺ����� ĳ���ʹ� ���� �������� ������ �� �ֵ��� ���ش�.
void AFPSCharacter::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::MoveRight(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}