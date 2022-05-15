// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnumTestActor.generated.h"

// 선언하고자 하는 열거형 선언하기
UENUM(BlueprintType)	// Blueprint에서도 사용이 가능하게 만든다.
enum class EMyColor : uint8
{
	Red UMETA(DisplayName = "Red"),
	Green UMETA(DisplayName = "Green"),
	Blue UMETA(DisplayName = "Blue"),
};

UCLASS()
class UNREAL_UENUM_API AEnumTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnumTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called Enum
	UPROPERTY(EditAnywhere)
		EMyColor MyColorTestEnum;
};
