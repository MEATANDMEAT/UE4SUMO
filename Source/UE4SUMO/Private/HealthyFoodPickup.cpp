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

	if (bEat)
	{
		Alpha = (FMath::Lerp(Alpha, 1.1f, 2.75f * DeltaTime));
		FoodMesh->SetWorldScale3D(FVector(Curve->GetFloatValue(Alpha)));
		if (Alpha >= 1)
		{
			Destroy();
			PrimaryActorTick.bCanEverTick = false;
		}
	}
}

void AHealthyFoodPickup::OnPlayerEnterPickupBox(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter && !bEat)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EatingSound, PlayerCharacter->GetActorLocation(), 1.f, 1.f, 0.f, nullptr, nullptr);
		PlayerCharacter->ChangeValues(SizeDecrease);
		bEat = true;
	}
	else 
	{

	}

}

