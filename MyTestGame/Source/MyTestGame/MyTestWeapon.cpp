// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestWeapon.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
AMyTestWeapon::AMyTestWeapon(const class FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent=WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));
	WeaponCollision->AttachTo(WeaponMesh, "DamageSocket");

	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	HitFX = ParticleAsset.Object;
}

void AMyTestWeapon::SetOwningPawn(AMyBasicCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AMyTestWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpesificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->AttachTo(PawnMesh, AttachPoint);
	}
}

void AMyTestWeapon::OnEquip(const AMyTestWeapon* LastWeapon)
{
	AttachMeshToPawn();
}

// Called when the game starts or when spawned
void AMyTestWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyTestWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTestWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AActor::StaticClass()) && MyPawn->isDuringAttack && OtherActor != MyPawn)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "ApplyDamage!!!");

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFX, GetActorLocation());
	}
}

