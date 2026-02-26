
#include "PD_EnemyProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"


APD_EnemyProjectile::APD_EnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 1.f;
	ProjectileMovement->InitialSpeed = 0.f;
	ProjectileMovement->MaxSpeed = 3000.f;
}

void APD_EnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APD_EnemyProjectile::OnBeginOverlap);

	GetWorld()->GetTimerManager().SetTimer(
		DestroyProjectileHandle, this, &APD_EnemyProjectile::MultiDestroyProjectile, 5.0f, false
	);
}

void APD_EnemyProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* SpawnActor = GetOwner();	// GetInstigator();
	
	if (SpawnActor != OtherActor && OtherActor != this)
	{
		MultiDestroyProjectile();
		
		if (auto* const Character = Cast<ACharacter>(OtherActor))
		{
			if (Character->GetController()->IsPlayerController())
			{
				// Damage
				return;
			}
		}
		
		// Spawn Particle
	}
}

void APD_EnemyProjectile::MultiDestroyProjectile_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(DestroyProjectileHandle);
	Destroy();
}
