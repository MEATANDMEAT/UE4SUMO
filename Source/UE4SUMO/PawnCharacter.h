// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnCharacter.generated.h"

UCLASS()
class UE4SUMO_API APawnCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Destroyed();

private:
	UPROPERTY(EditAnywhere)
		FTransform CameraTransform;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	USpringArmComponent* SpringArm;
	UCameraComponent* Camera;
	FTimerHandle MovementHandle;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector MOVE_UP = FVector(100.f, 0.f, 0.f);
	FVector MOVE_DOWN = FVector(-100.f, 0.f, 0.f);
	FVector MOVE_RIGHT = FVector(0.f, -100.f, 0.f);
	FVector MOVE_LEFT = FVector(0.f, 100.f, 0.f);
	FVector MOVEMENT = FVector(0.f, 0.f, 0.f);
	float Reach = 100.f;
	bool PlayerCanMove;
	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	bool Object(FVector myVector);

	float timeSinceMoved;
};
