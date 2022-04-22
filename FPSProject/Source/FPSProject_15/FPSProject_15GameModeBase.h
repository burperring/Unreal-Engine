// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSProject_15GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_15_API AFPSProject_15GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	// �α� �޼����� ����ؼ� �𸮾� �������� �����Ǵ� �⺻ GameMode�� �ƴ� FPSProject_15GameModeBase�� ������ ���Ǵ��� �����غ���.
public:
	virtual void StartPlay() override;
};
