// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransferVolum.h"
#include "LEVEL_MOVE_18Character.h"
#include <Engine/Classes/Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ALevelTransferVolum::ALevelTransferVolum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TransferVolum = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolum"));
	RootComponent = TransferVolum;
	TransferVolum->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

// Called when the game starts or when spawned
void ALevelTransferVolum::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelTransferVolum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransferVolum::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ALEVEL_MOVE_18Character* Character = Cast<ALEVEL_MOVE_18Character>(OtherActor);
	if (Character)
	{
		// 레벨을 이동시키기 위한 클래스(맵에서 다른 맵으로 이동)
		UGameplayStatics::OpenLevel(GetWorld(), FName(TransferLevelName));
	}
}