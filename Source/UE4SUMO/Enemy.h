// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Classes/Engine/World.h"

#include "Enemy.generated.h"

UCLASS()
class UE4SUMO_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

int posX;
int posY;

UPROPERTY(EditAnywhere, Category = "Mesh")
UStaticMeshComponent* MeshComponent;

UPROPERTY(EditAnywhere)
float MoveTimer = 0.3;

void Move();

bool Trace();

bool bMoving = false;

bool bSeesPlayer = false;

float playerDistance = 0.f;

FTimerHandle MemberTimerHandle;
};
