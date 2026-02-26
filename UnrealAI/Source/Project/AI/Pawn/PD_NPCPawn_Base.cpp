
#include "PD_NPCPawn_Base.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Project4/AI/Component/PD_NPCFloatingPawnMovement.h"

APD_NPCPawn_Base::APD_NPCPawn_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UPD_NPCFloatingPawnMovement>(TEXT("MovementComponent"));
}

void APD_NPCPawn_Base::Attack()
{
}

void APD_NPCPawn_Base::SpecialAttack()
{
}

void APD_NPCPawn_Base::BeginPlay()
{
	Super::BeginPlay();
	
}
