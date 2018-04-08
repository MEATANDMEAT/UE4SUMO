// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthyFoodPickup.h"


// Sets default values
AHealthyFoodPickup::AHealthyFoodPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FoodRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = FoodRoot;
	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh"));
	FoodMesh->SetupAttachment(FoodRoot);

	FoodBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FoodBox"));
	FoodBox->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	FoodBox->bGenerateOverlapEvents = true;
	FoodBox->OnComponentBeginOverlap.AddDynamic(this, &AHealthyFoodPickup::OnPlayerEnterPickupBox);
	FoodBox->SetupAttachment(FoodRoot);
}

// Called when the game starts or when spawned
void AHealthyFoodPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthyFoodPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthyFoodPickup::OnPlayerEnterPickupBox(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	TArray<USkeletalMeshComponent*> Comps;
	if (PlayerCharacter) {
		OtherActor->GetComponents(Comps);
		if (Comps.Num() > 0)
		{
			USkeletalMeshComponent* FoundComp = Comps[0];
			Comps[0]->SetWorldScale3D(Comps[0]->GetComponentScale() - SizeDecrease);
		}
		PlayerCharacter->Speed += SpeedUp;
		Destroy();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("A Non-Player stepped on this HealthyFoodPickup"));
	}

}

