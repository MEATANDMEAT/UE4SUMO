// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Customer headers
#include "PlayerCharacter.h"

//Engine specific headers
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

//Required headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelExit.generated.h"

UCLASS()
class UE4SUMO_API ALevelExit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelExit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		USceneComponent* WorldStaticRoot = nullptr;

	UPROPERTY(EditAnywhere)
		UShapeComponent* WorldStaticBox = nullptr;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnPlayerOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
