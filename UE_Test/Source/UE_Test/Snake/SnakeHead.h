// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakePart.h"
#include "SnakeHead.generated.h"

/**
 * 
 */
UCLASS()
class UE_TEST_API ASnakeHead : public ASnakePart
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnakeHead();

	FVector MovePos;
	AActor* NewPart = nullptr;

	TArray<AActor*> AllBodyActor;
	FVector PrevPart;
	FVector LastPart;
	FVector TempPos;

	void MovePart();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "GameModeValue", EditAnywhere, DisplayName = "PartObjClass")
		TSubclassOf<AActor> BodyType;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
		void LeftMove(float _Value);

	UFUNCTION(BlueprintCallable)
		void RightMove(float _Value);

	UFUNCTION(BlueprintCallable)
		void UpMove(float _Value);

	UFUNCTION(BlueprintCallable)
		void DownMove(float _Value);

	UFUNCTION(BlueprintCallable)
		void LeftAction();

	UFUNCTION(BlueprintCallable)
		void RightAction();

	UFUNCTION(BlueprintCallable)
		void UpAction();

	UFUNCTION(BlueprintCallable)
		void DownAction();

	void IsBodyCheck();

	void CreateNewPart();

	
};
