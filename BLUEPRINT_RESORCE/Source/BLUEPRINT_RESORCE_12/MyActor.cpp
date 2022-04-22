// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ConstructorHelpers는 C++ 클래스의 생성자에서 프로젝트에 포함된 블루프린트 클래스나 에셋을 가져오기 위해서 사용된다.
	// ConstructorHelpers는 생성자에서 클래스를 초기화하는데 도움을 주는 클래스로 콘텐츠 브라우저의 리소스나
	// 블루프린트 클래스를 불러오는 작업을 도와주는 기능을 가지고 있다.
	// 그리고 ConstructorHelpers 클래스는 생성자 이외의 코드에서 이 클래스를 사용하려고 시도하면 컴파일 에러가 발생하기 때문에
	// 생성자 함수에서만 사용해야 한다.
	// <>안에는 블루프린트 클래스 타입을 넣어줘야 하는데 블루프린트 자체에 클래스 타입이 없기 때문에 
	// 블루프린트가 상속받는 C++ 클래스의 타입을 넣어주면 된다.
	static ConstructorHelpers::FClassFinder<APawn> BpClass(TEXT("/Game/StarterContent/BP_TestClass"));

	// 여기서 블루프린트 클래스나 에셋을 가져올때는 문자열로 직접 경로를 적어서 불러오는 방식이여서 오타나 변경된 경로 혹은 파일명으로 인해서
	// 클래스가 제대로 불러오지 않는 경우가 발생할 수 있다.
	// 이러한 경우를 없애기 위해서 Succeeded 함수와 Class의 NULL 체크를 통해 블루프린트가 성공적으로 불러와졌는지 체크하고 사용해야 한다.
	if (BpClass.Succeeded() && BpClass.Class != NULL)
	{
		// BpClass.Class.
		// BpClass.Class->
	}

	UStaticMeshComponent* MeshComponent = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	if (MeshAsset.Succeeded() && MeshAsset.Object != NULL)
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
	}
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

}

