// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	// 다운 캐스트를 해야합니다.
	if (nullptr == GameModePtr)
	{
		// 이 TEXT에 대해서도 설명하자면
		// 언리얼에서는 유니코드 멀티바이트를 구분하지 않는다.
		// 어떤 국가코드와 언리얼엔진이 알아서 찾아준다.
		// 문자열은 여러개의 인코딩이 있는에 그 인코딩을 알아서 자신들이 처리하겠다는 의미로
		// TEXT() 알아서 유니코드건 멀티바이트건 뭐건 알아서 잘 처리하겠다.
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	if (false == GameModePtr->IsValidLowLevel())
	{
		// 언리얼의 검사상 이포인터는 위험할 가능성이 있다는것이다.
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	// 다운캐스팅
	ASnakeGameMode* SnakeGameMode = Cast<ASnakeGameMode>(GameModePtr);

	if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return;
	}

	FIntVector3 Count = SnakeGameMode->GetCount();
	FVector Size = SnakeGameMode->GetTileSize();
	// /가 사칙연산중 가장 느린 연산입니다.
	// /2 할바에는 *0.5f

	FVector Center = { -1000.0f, Size.Y * Count.Y * 0.5f, Size.Z * Count.Z * 0.5f };

	SetActorLocation(Center);
	
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASnakePawn::HeadPositionToCenter()
{

	AGameModeBase* GameModePtr = UGameplayStatics::GetGameMode(GetWorld());
	if (nullptr == GameModePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	if (false == GameModePtr->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == GameMode)"), __FUNCTION__, __LINE__);
		return;
	}

	ASnakeGameMode* SnakeGameMode = Cast<ASnakeGameMode>(GameModePtr);

	if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == SnakeGameMode && false == SnakeGameMode->IsValidLowLevel())"), __FUNCTION__, __LINE__);
		return;
	}

	FIntVector3 Count = SnakeGameMode->GetCount();
	FIntVector3 CenterCount;
	// 정수는 0.5가 없다.
	CenterCount.Y = (Count.Y) / 2;
	CenterCount.Z = (Count.Z) / 2;
	FVector Size = SnakeGameMode->GetTileSize();

	FVector Center = { 0.0f, Size.Y * CenterCount.Y, Size.Z * CenterCount.Z };

	Head->SetActorLocation(Center);
}

