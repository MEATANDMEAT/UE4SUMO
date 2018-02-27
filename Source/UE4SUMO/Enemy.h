// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
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

private:
	FTimerHandle MemberTimerHandle;

    UPROPERTY(EditAnywhere, Category = "Mesh")
    UStaticMeshComponent* EnemyMesh;  
    UPROPERTY(EditAnywhere)
    float MoveTimer = 0.3;
	UPROPERTY(EditAnywhere)
	UShapeComponent* EnemyBox;
	APawn* Pawn;
	FHitResult HitOut = FHitResult(0);
	FHitResult PawnHit = FHitResult(0);
	int posX;
	int posY;
    bool bMoving = false;
	void Move();
	bool Trace();

	UFUNCTION()
		void OnEnemyHitPawn(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
