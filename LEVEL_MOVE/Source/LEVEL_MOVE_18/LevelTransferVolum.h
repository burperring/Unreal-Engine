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

	// BoxComponent�� ������Ʈ ������ ó���� �̺�Ʈ �Լ� ����
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// �� ������ ����� �� �ҷ��� ���� �̸��� ������ ����
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		FString TransferLevelName;

	// ĳ���͸� �����ϴ� �ݸ������� ����� UBoxComponent ������ Ÿ���� ����
	UPROPERTY()
		class UBoxComponent* TransferVolum;
};
