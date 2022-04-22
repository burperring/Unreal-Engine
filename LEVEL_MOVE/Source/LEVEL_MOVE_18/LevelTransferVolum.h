// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransferVolum.generated.h"

UCLASS()
class LEVEL_MOVE_18_API ALevelTransferVolum : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTransferVolum();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// BoxComponent의 오브젝트 감지를 처리할 이벤트 함수 선언
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// 이 볼륨에 닿았을 때 불러올 씬의 이름을 저장할 변수
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString TransferLevelName;

	// 캐릭터를 감지하는 콜리전으로 사용할 UBoxComponent 포인터 타입의 변수
	UPROPERTY()
		class UBoxComponent* TransferVolum;
};
