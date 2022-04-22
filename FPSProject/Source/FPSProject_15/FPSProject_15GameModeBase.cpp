// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSProject_15GameModeBase.h"

void AFPSProject_15GameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	}
	// 헤더 파일과 C++ 파일에 모든 선언이 완료 되었다면 로그가 잘 출력되는지 확인해야 한다.
	// 로그를 출력하기 위해서는 C++ 클래스에 있는 FPSProject_15GameModeBase 파일의 블루프린트를 만든 다음에
	// 편집 -> 프로젝트 세팅 -> 맵&모드에 들어가서 "기본 게임 모드"를 새로 만든 블루프린트(BP_FPSPro....)로 선언해주면 로그가 출력되는 모습을 볼 수 있다.
}