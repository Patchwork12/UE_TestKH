// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeHead.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
	// �𸮾󿡼� �����Ӹ��� Tick�� ������ �ϴ� ���ʹ�
	// PrimaryActorTick.bCanEverTick = true; �� �������� Tick�� �������� �ֽ��ϴ�.

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// �����ڿ��� ���� �������ִ°� �Ϲ����ε�. 
	// ƽ�� �����ų� ���ų�
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

//�ٵ� ������ üũ
void ASnakeHead::IsBodyCheck()
{
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		Body->Destroy();
		GetSnakeGameMode()->CurBodyReset();

		CreateNewPart();
		//"BodyPart" �±װ� �ִ� ������Ʈ�� ã�´�
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "BodyPart", AllBodyActor);

	}
}

//�� ���� ����� �Լ�
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

//������ ������ ������ ���� ������� �Լ�
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


