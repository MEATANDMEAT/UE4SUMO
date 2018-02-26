// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodPickup.h"


// Sets default values
AFoodPickup::AFoodPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	FoodRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = FoodRoot;
	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FoodMesh"));
	FoodMesh->AttachToComponent(FoodRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);

	FoodBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FoodBox"));
	FoodBox->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	FoodBox->bGenerateOverlapEvents = true;
	FoodBox->OnComponentBeginOverlap.AddDynamic(this, &AFoodPickup::OnPlayerEnterPickupBox);
	FoodBox->AttachToComponent(FoodRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void AFoodPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFoodPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFoodPickup::OnPlayerEnterPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
TArray<UStaticMeshComponent*> Comps;
 
 OtherActor->GetComponents(Comps);
 if(Comps.Num() > 0)
 {
     UStaticMeshComponent* FoundComp = Comps[0];
        Comps[0]->SetWorldScale3D(Comps[0]->GetComponentScale()+SizeIncrease);
 }
	Destroy();
}

