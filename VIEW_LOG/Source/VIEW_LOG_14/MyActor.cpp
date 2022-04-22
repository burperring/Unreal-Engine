// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
// �������Ʈ���� ������ �� ó�� C++������ ��·α׿� �α׸� ���� ���� ���
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// C++ Ŭ�������� ����Ʈ�� ȭ�鿡 �α׸� ���� ���ؼ��� AddOnScreenDebugMessage �Լ��� ����ϸ� �ȴ�.
	// �̶� ù ��° �Ű������� �α׸� ���� �� �տ��� ��� �α׸� ����� ����� �ƴϸ� ���� �ٷ� �о�� ������� �����Ѵ�.
	// ���⼭ -1�� �����ϸ� �տ��� ��� �α׸� ���� �ٷ� �о�� �α׸� ����, -1�� �ƴ� ������ �����ϸ� ���� �α׸� ����� �� �α׸� ����.
	// �� ��° �Ű������� ȭ�鿡 ���� �α��� �ð��̰� �� ��° �Ű������� �α��� �����̴�.
	// ���������� �� ��° �Ű������� ����� �α��� ������ ������ �ȴ�.
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Red, TEXT("HELLO 2"));

	// �տ��� ��������� ������� �� UKismetSystemLibrary Ŭ������ PrintString �Լ��� ȣ���ϸ�
	// �������Ʈ�� ����� �״�� ����� �� ������ �Ű����� ���� �������Ʈ���� ����ϴ� �״�� ����� �����ϴ�.
	// �ٸ� ù ��° �Ű������� UObject ������ Ÿ���� WorldContextObject��� ���� �䱸�ϴµ� ���⿡�� �����ϰ�
	// GetWorld() �Լ��� ȣ���ؼ� ��ȯ�Ǵ� ���带 �־��ָ� �ȴ�.
	// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hello 3"), true, true, FLinearColor::Green, 2.0f);
}

