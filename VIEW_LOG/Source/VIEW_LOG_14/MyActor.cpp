// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
// 블루프린트에서 설정한 것 처럼 C++에서도 출력로그에 로그를 띄우기 위한 방법
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

	// C++ 클래스에서 뷰포트의 화면에 로그를 띄우기 위해서는 AddOnScreenDebugMessage 함수를 사용하면 된다.
	// 이때 첫 번째 매개변수는 로그를 남길 때 앞에서 띄운 로그를 지우고 띄울지 아니면 다음 줄로 밀어내고 띄울지를 결정한다.
	// 여기서 -1로 설정하면 앞에서 띄운 로그를 다음 줄로 밀어내고 로그를 띄우고, -1이 아닌 값으로 설정하면 전의 로그를 지우고 새 로그를 띄운다.
	// 두 번째 매개변수는 화면에 띄우는 로그의 시간이고 세 번째 매개변수는 로그의 색상이다.
	// 마지막으로 네 번째 매개변수에 출력할 로그의 내용을 적으면 된다.
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Red, TEXT("HELLO 2"));

	// 앞에서 헤더파일을 선언받은 후 UKismetSystemLibrary 클래스의 PrintString 함수를 호출하면
	// 블루프린트의 기능을 그대로 사용할 수 있으며 매개변수 역시 블루프린트에서 사용하던 그대로 사용이 가능하다.
	// 다만 첫 번째 매개변수로 UObject 포인터 타입의 WorldContextObject라는 것을 요구하는데 여기에는 간단하게
	// GetWorld() 함수를 호출해서 반환되는 월드를 넣어주면 된다.
	// UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Hello 3"), true, true, FLinearColor::Green, 2.0f);
}

