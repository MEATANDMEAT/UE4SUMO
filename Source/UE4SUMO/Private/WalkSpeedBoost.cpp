// Fill out your copyright notice in the Description page of Project Settings.

#include "WalkSpeedBoost.h"


// Sets default values
AWalkSpeedBoost::AWalkSpeedBoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	Box->bGenerateOverlapEvents = true;
	Box->OnComponentBeginOverlap.AddDynamic(this, &AWalkSpeedBoost::OnPlayerEnterPickupBox);
	Box->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AWalkSpeedBoost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWalkSpeedBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPickup)
	{
		Alpha = (FMath::Lerp(Alpha, 1.1f, 2.75f * DeltaTime));
		Mesh->SetWorldScale3D(FVector(Curve->GetFloatValue(Alpha)));
	}

}

void AWalkSpeedBoost::OnPlayerEnterPickupBox(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter && !bPickup)
	{
		GetWorldTimerManager().SetTimer(Timer, this, &AWalkSpeedBoost::SpeedBoost, 1.f, true, 0.f);
		bPickup = true;
	}
}

void AWalkSpeedBoost::SpeedBoost()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Repeats++;
	if (Repeats < 5)
	{
		PlayerCharacter->Speed = 400.f;
		UE_LOG(LogTemp, Warning, TEXT("Speed 400"));
	}
	else if (Repeats > 5)
	{
		GetWorldTimerManager().ClearTimer(Timer);
		UE_LOG(LogTemp, Warning, TEXT("Speed 300"));
		PlayerCharacter->Speed = 300.f;
		Repeats = 0;
		Destroy();
	}

}

