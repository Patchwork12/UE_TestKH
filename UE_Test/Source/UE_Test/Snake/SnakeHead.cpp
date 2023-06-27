// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
	// 언리얼에서 프레임마다 Tick을 돌려야 하는 액터는
	// PrimaryActorTick.bCanEverTick = true; 로 만들어줘야 Tick을 돌릴수가 있습니다.

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 생성자에서 보통 설정해주는게 일반적인데. 
	// 틱을 돌릴거냐 말거냐
	PrimaryActorTick.bCanEverTick = true;
	// PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;


}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnakeHead::LeftMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}

	AddActorLocalOffset(FVector::LeftVector);
}


void ASnakeHead::RightMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}

	AddActorLocalOffset(FVector::RightVector);
}
void ASnakeHead::UpMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}
	AddActorLocalOffset(FVector::UpVector);
}
void ASnakeHead::DownMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}
	AddActorLocalOffset(FVector::DownVector);
}

void ASnakeHead::LeftAction()
{

	MovePos = FVector::LeftVector * 100.0f;



	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "BodyPart"))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> Game Over"), __FUNCTION__, __LINE__);

	}

	if (this->GetActorLocation() + MovePos == TempPos)
	{
		return;
	}

	PrevPos = this->GetActorLocation();
	TempPos = this->GetActorLocation();

	AddActorLocalOffset(FVector::LeftVector * 100.0f);


	IsBodyCheck();

	MovePart();


}
void ASnakeHead::RightAction()
{
	MovePos = FVector::RightVector * 100.0f;



	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "BodyPart"))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> Game Over"), __FUNCTION__, __LINE__);

	}

	if (this->GetActorLocation() + MovePos == TempPos)
	{
		return;
	}

	PrevPos = this->GetActorLocation();
	TempPos = this->GetActorLocation();

	AddActorLocalOffset(FVector::RightVector * 100.0f);



	IsBodyCheck();

	MovePart();

}
void ASnakeHead::UpAction()
{
	MovePos = FVector::UpVector * 100.0f;


	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "BodyPart"))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> Game Over"), __FUNCTION__, __LINE__);

	}

	if (this->GetActorLocation() + MovePos == TempPos)
	{
		return;
	}


	PrevPos = this->GetActorLocation();
	TempPos = this->GetActorLocation();

	AddActorLocalOffset(FVector::UpVector * 100.0f);


	IsBodyCheck();
	MovePart();

}
void ASnakeHead::DownAction()
{
	MovePos = FVector::DownVector * 100.0f;


	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "Wall"))
	{
		return;
	}

	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + MovePos, "BodyPart"))
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> Game Over"), __FUNCTION__, __LINE__);


	}

	if (this->GetActorLocation() + MovePos == TempPos)
	{
		return;
	}


	PrevPos = this->GetActorLocation();
	TempPos = this->GetActorLocation();



	AddActorLocalOffset(FVector::DownVector * 100.0f);

	IsBodyCheck();


	MovePart();

}

//바디 아이템 체크
void ASnakeHead::IsBodyCheck()
{
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();

		CreateNewPart();
		//"BodyPart" 태그가 있는 오브젝트를 찾는다
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "BodyPart", AllBodyActor);

	}
}

//새 파츠 만드는 함수
void ASnakeHead::CreateNewPart()
{

	FTransform Trans;
	int32 Count = AllBodyActor.Num();

	if (0 > Count)
	{
		return;
	}
	else if (0 == Count)
	{
		Trans.SetLocation({ PrevPos });
		NewPart = GetWorld()->SpawnActor<AActor>(BodyType, Trans);
	}
	else if (0 != Count)
	{
		LastPart = AllBodyActor[Count - 1]->GetActorLocation();
		Trans.SetLocation({ LastPart });
		NewPart = GetWorld()->SpawnActor<AActor>(BodyType, Trans);
	}


	int a = 0;

}

//움직일 때마다 파츠가 같이 따라오는 함수
void ASnakeHead::MovePart()
{

	int32 Count = AllBodyActor.Num();
	for (int i = 0; i < Count; i++)
	{
		PrevPart = PrevPos;
		PrevPos = AllBodyActor[i]->GetActorLocation();
		AllBodyActor[i]->SetActorLocation(PrevPart);

	}
}


