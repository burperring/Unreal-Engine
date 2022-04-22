// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
// GetCapsuleComponent() 함수의 오류를 해결하기 위한 헤더파일
#include <Engine/Classes/Components/CapsuleComponent.h>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 헤더 파일에서 선언한 UCameraComponent를 생성자 함수에 생성해서 카메라의 위치를 눈 위치보다 살짝 높은 곳으로 잡고
	// 폰이 카메라 로테이션을 제어하도록 코드를 작성한다.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0 + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	// 1인칭 스켈레탈 Mesh 컴포넌트 생성하고 소유주는 해당 Mesh를 볼 수 있게 만든다.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);			// 자기 자신에게만 해당 Mesh가 보이게 설정해주고 카메라에 붙인다.
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;	// 해당 Mesh는 그림자가 보이지 않게 만든다.
	FPSMesh->CastShadow = false;

	// 3인칭 Mesh를 불러와서 소유주는 해당 Mesh를 볼 수 없게 만든다.
	GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// GameMode에서 확인하는 것 처럼 FPSCharacter가 재대로 사용되는지 확인하기 위한 로그를 띄워준다.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter!"));
	}
	// 마찬가지로 선언 이후 언리얼 엔진에 돌아가서 FPSCharacter기반의 블루프린트를 생성해준다.
	// 생성 이후 편집 -> 프로젝트 세팅 -> 맵&모드 -> 선택된 GameMode에 들어가서 Default Pawn Class를 찾아 BP_FPSCharacter로 변경해준다.
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

	// 함수 구현이 끝나면 움직임에 해당 함수들을 바인딩 시켜준다.
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// 마우스 상하좌우 움직임의 경우 기본적으로 제공되는 값이 존재하기 때문에 새롭게 함수를 선언할 필요가 없다.
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);		// X축 움직임
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);	// Y축 움직임

	// 점프 함수에 대한 선언을 바인딩 해준다.
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	// 발사에 관련된 함수 바인딩
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
}

// FPS에서 캐릭터의 움직임을 구현하기 위해서는 카메라의 방향에 따른 움직임을 구현해야 한다.
// "전방"은 "카메라가 향하는 방향"을 의미하고 "측면"은 "카메라가 향하는 방향의 측면"을 의미한다.
// 캐릭터의 제어 방향을 구하는 데는 PlayerController를 사용한다.
// 또한 MoveForward 함수에서는 제어 회전의 피치 컴포넌트를 무시하고 입력을 XY 면으로 제한시켜
// 위나 아래를 처다보더라도 캐릭터는 땅과 평행으로 움직일 수 있도록 해준다.
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