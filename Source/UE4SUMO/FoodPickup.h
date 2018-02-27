// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodPickup.generated.h"

UCLASS()
class UE4SUMO_API AFoodPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Set up static mesh for our pickup
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* FoodMesh;
	UPROPERTY(EditAnywhere)
	USceneComponent* FoodRoot;
	UPROPERTY(EditAnywhere)
    UShapeComponent* FoodBox;

	UPROPERTY(EditAnywhere)
    float SizeIncrease = 0.1f;
private:
	UFUNCTION()
		void OnPlayerEnterPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
