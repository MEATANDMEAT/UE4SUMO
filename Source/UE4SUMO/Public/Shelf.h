// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Custom headers
#include "FoodPickup.h"

//Engine specific headers
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

//Required headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shelf.generated.h"

UCLASS()
class UE4SUMO_API AShelf : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShelf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* WorldStaticMesh = nullptr;

	UPROPERTY(EditAnywhere)
		USceneComponent* WorldStaticRoot = nullptr;

	UPROPERTY(EditAnywhere)
		UShapeComponent* WorldStaticBox = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AFoodPickup> Food;

	bool bAllowSpawn = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
