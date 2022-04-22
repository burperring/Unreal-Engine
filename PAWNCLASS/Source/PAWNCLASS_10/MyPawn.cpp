// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
// UCameraComponent�� ����ϱ� ���� �������
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������ ���۵Ǹ� �ڵ����� �÷��̾��� �Է��� ����ǵ��� ����� �� ��
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	// ���� �Է� ������ �ϱ� ���ؼ� �𸮾� �������� ���ư��� �����Ѵ�
	// �𸮾� �������� ���� -> ������Ʈ ���� -> �Է� �׸����� ����
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		float CurrentScale = OurVisibleComponent->GetComponentScale().X;
		if (bGrowing)
		{
			if (InputTime > 0.0f && InputTime <= 0.5f)
			{
				CurrentScale = 2.0f;
			}
			else 
			{
				CurrentScale += DeltaTime;
			}
		}
		else
		{
			CurrentScale -= DeltaTime * 0.5f;
		}
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
	}

	{
		if (!CurrentVelocity.IsZero())
		{
			InputTime += DeltaTime;
			InputTime = FMath::Clamp(InputTime, 0.0f, 5.0f);
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime * InputTime);
			SetActorLocation(NewLocation);
		}
		else
		{
			InputTime = 0.0f;
		}
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ���⼭ ���ε� �۾��� ����ȴ�
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

// �Ʒ� �Լ����� �Է� ���ΰ� ������� ��� �Ѵ�
// �̷��� �۾��� �Լ��� �Է��� ���´ٴ� ������ "���ε��Ѵ�"��� ǥ���Ѵ�
void AMyPawn::Move_XAxis(float AxisValue)
{
	// AxisValue�� Clamp �Լ��� �̿��ؼ� -1���� 1������ ������ ������ �� 100�� ���ؼ� CurrentVelocity�� X�� �����ϵ��� �Ѵ�
	// ���⼭ AxisValue ���� �����ϴ� ������ MoveX �Է� ���ο� WŰ�� ��Ű�� ��� ��ϵǾ� ���� �� 
	// �� Ű�� ���ÿ� ������ �� ���� �ջ�Ǿ� AxisValue�� ���޵Ǳ� �����̴�
	// �׷��� �̰��� �������� ������ �� Ű�� ���ÿ� �Է��ϸ� �̵��ӵ��� 2�谡 �Ǵ� ���װ� �߻��ϰ� �ȴ�
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}