// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom headers
#include "PlayerCharacter.h"

//Engine specific headers
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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

	UPROPERTY(EditAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UShapeComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* OverlapSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ScoreNeeded = 40000.f;

private:
	UFUNCTION()
		void OnPlayerEnterPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
};
