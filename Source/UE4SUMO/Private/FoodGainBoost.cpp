// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodGainBoost.h"


// Sets default values
AFoodGainBoost::AFoodGainBoost()
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
	FoodBox->OnComponentBeginOverlap.AddDynamic(this, &AFoodGainBoost::OnPlayerEnterPickupBox);
	FoodBox->SetupAttachment(FoodRoot);
}

// Called when the game starts or when spawned
void AFoodGainBoost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodGainBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPickup)
	{
		Alpha = (FMath::Lerp(Alpha, 1.1f, 2.75f * DeltaTime));
		FoodMesh->SetWorldScale3D(FVector(Curve->GetFloatValue(Alpha)));
		if (Alpha >= 1)
		{
			Destroy();
			PrimaryActorTick.bCanEverTick = false;
		}	
	}
	if (Beta >= 1.f)
	{
		bUp = !bUp;
		Beta = 0.f;
	}
	Beta = (FMath::Lerp(Beta, 1.1f, 1.9f*DeltaTime));
	if (bUp) FoodMesh->AddRelativeLocation(FVector(0.f, 0.f, CurveFloating->GetFloatValue(Beta))*30.f*DeltaTime);
	else FoodMesh->AddRelativeLocation(FVector(0.f, 0.f, CurveFloating->GetFloatValue(Beta)*-30.f*DeltaTime));
	FoodMesh->AddRelativeRotation(FRotator(0.f, 73.f*DeltaTime, 0.f));
}

void AFoodGainBoost::OnPlayerEnterPickupBox(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter && !bPickup)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AFoodGainBoost::FoodGain, 1.f, true, 0.f);
		bPickup = true;
	}
}

void AFoodGainBoost::FoodGain()
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Repeats++;
	if (Repeats < 5)
	{
		PlayerCharacter->SizeIncrease = 0.3f;
		UE_LOG(LogTemp, Warning, TEXT("Food gain has increased"));
	}
	else if (Repeats > 5)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Food gain has decreased"));
		PlayerCharacter->SizeIncrease = 0.1f;
		Repeats = 0;
		Destroy();
	}

}

