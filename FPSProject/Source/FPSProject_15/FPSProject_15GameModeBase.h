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
	
	// 로그 메세지를 사용해서 언리얼 엔진에서 제공되는 기본 GameMode가 아닌 FPSProject_15GameModeBase가 실제로 사용되는지 점검해본다.
public:
	virtual void StartPlay() override;
};
