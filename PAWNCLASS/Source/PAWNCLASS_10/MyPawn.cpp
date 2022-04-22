// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
// UCameraComponent를 사용하기 위한 헤더파일
#include <Engine/Classes/Camera/CameraComponent.h>

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 게임이 시작되면 자동으로 플레이어의 입력이 연결되도록 만들어 준 것
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	// 이후 입력 매핑을 하기 위해서 언리얼 엔진으로 돌아가서 정의한다
	// 언리얼 엔젠에서 편집 -> 프로젝트 세팅 -> 입력 항목으로 들어간다
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

	// 여기서 바인딩 작업이 진행된다
	PlayerInputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	PlayerInputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
}

// 아래 함수들을 입력 매핑과 연결시켜 줘야 한다
// 이러한 작업을 함수와 입력을 묶는다는 뜻으로 "바인딩한다"라고 표현한다
void AMyPawn::Move_XAxis(float AxisValue)
{
	// AxisValue를 Clamp 함수를 이용해서 -1에서 1사이의 값으로 제한한 뒤 100을 곱해서 CurrentVelocity의 X에 저장하도록 한다
	// 여기서 AxisValue 값을 제한하는 이유는 MoveX 입력 매핑에 W키와 ↑키가 모두 등록되어 있을 때 
	// 두 키를 동시에 누르면 두 값이 합산되어 AxisValue로 전달되기 때문이다
	// 그래서 이것을 제한하지 않으면 두 키를 동시에 입력하면 이동속도가 2배가 되는 버그가 발생하게 된다
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