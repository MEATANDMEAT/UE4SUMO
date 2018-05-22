// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodPickup.h"


// Sets default values
AFoodPickup::AFoodPickup()
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
	FoodBox->OnComponentBeginOverlap.AddDynamic(this, &AFoodPickup::OnPlayerEnterPickupBox);
	FoodBox->SetupAttachment(FoodRoot);
}

// Called when the game starts or when spawned
void AFoodPickup::BeginPlay()
{
	Super::BeginPlay();
	Alpha = FMath::RandRange(-2.5f, 0.f);
	bEat = false;
}

// Called every frame
void AFoodPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEat)
	{
		Alpha = (FMath::Lerp(Alpha, 1.1f, 2.75f * DeltaTime * FMath::RandRange(0.8f, 1.3f)));

		FoodMesh->SetWorldScale3D(FVector(Curve->GetFloatValue(Alpha)));
		if (Alpha >= 1)
		{
			Destroy();
			PrimaryActorTick.bCanEverTick = false;
		}
	}
}

void AFoodPickup::OnPlayerEnterPickupBox(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	if (PlayerCharacter && !bEat)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), EatingSound, 1.f, 1.f);
		PlayerCharacter->ChangeValues(SizeIncrease);
		bEat = true;
		GetWorld()->SpawnActor<AScoreSplash>(
			ScoreSplash->GetAuthoritativeClass(), 
			FVector((PlayerCharacter->GetActorLocation().X) + FMath::RandRange(0.f, 200.f), (PlayerCharacter->GetActorLocation().Y) + FMath::RandRange(0.f, 200.f), PlayerCharacter->GetActorLocation().Z * 2), 
			FRotator(0.f, 0.f, 0.f), 
			SpawnInfo);
	}
}