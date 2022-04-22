// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPSProject_15GameModeBase.h"

void AFPSProject_15GameModeBase::StartPlay()
{
	Super::StartPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	}
	// ��� ���ϰ� C++ ���Ͽ� ��� ������ �Ϸ� �Ǿ��ٸ� �αװ� �� ��µǴ��� Ȯ���ؾ� �Ѵ�.
	// �α׸� ����ϱ� ���ؼ��� C++ Ŭ������ �ִ� FPSProject_15GameModeBase ������ �������Ʈ�� ���� ������
	// ���� -> ������Ʈ ���� -> ��&��忡 ���� "�⺻ ���� ���"�� ���� ���� �������Ʈ(BP_FPSPro....)�� �������ָ� �αװ� ��µǴ� ����� �� �� �ִ�.
}