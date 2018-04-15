// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom headers
#include "PlayerCharacter.h"

//Engine specific headers
#include "Runtime/Engine/Classes/Components/ShapeComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"

//Required headers
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodGainBoost.generated.h"

UCLASS()
class UE4SUMO_API AFoodGainBoost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodGainBoost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* FoodMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent* FoodRoot;

	UPROPERTY(EditAnywhere)
		UShapeComponent* FoodBox;

	UPROPERTY(EditDefaultsOnly, Category = Curve)
		UCurveFloat* Curve;

	float Alpha = 0.f;

	bool bPickup = false;

	unsigned int Repeats = 0;

	FTimerHandle Timer;

private:
	UFUNCTION()
		void OnPlayerEnterPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void FoodGain();
};
