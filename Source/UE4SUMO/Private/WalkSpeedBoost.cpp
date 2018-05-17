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
	Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
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

	if (Beta >= 1.f) 
	{
		bUp = !bUp;
		Beta = 0.f;
	}
	Beta = (FMath::Lerp(Beta, 1.1f, 1.9f*DeltaTime));

	if (bUp) Mesh->AddRelativeLocation(FVector(0.f, 0.f, CurveFloating->GetFloatValue(Beta))*30.f*DeltaTime);
	else Mesh->AddRelativeLocation(FVector(0.f, 0.f, CurveFloating->GetFloatValue(Beta)*-30.f*DeltaTime));
	Mesh->AddRelativeRotation(FRotator(0.f, 73.f*DeltaTime, 0.f));
}

void AWalkSpeedBoost::OnPlayerEnterPickupBox(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter && !bPickup && !PlayerCharacter->bSpeedPickup)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SpeedBoostSound, 0.2f, 1.f, 0, nullptr, PlayerCharacter);
		UGameplayStatics::PlaySound2D(GetWorld(), SodaSound, 1.f, 1.f, 0.5f, nullptr, PlayerCharacter);
		if (Player->bDashing)
		{
			GetWorldTimerManager().SetTimer(DelayTimer, this, &AWalkSpeedBoost::DashDelay, 1.f, false, 0.3f);
		} 
		else if (!Player->bDashing)
		{
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AWalkSpeedBoost::SpeedBoost, 1.f, true, 0.f);
			Player->bSpeedPickup = true;
			Player->Speed += 100.f;
			bPickup = true;
		}
	}
}

void AWalkSpeedBoost::SpeedBoost()
{
	if (Repeats > 0)
	{
        Repeats--;
	}
	else if (Repeats <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Player->Speed -= 100.f;
		Player->bSpeedPickup = false;
		Destroy();
	}

}

void AWalkSpeedBoost::DashDelay()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWalkSpeedBoost::SpeedBoost, 1.f, true, 0.f);
	Player->bSpeedPickup = true;
	Player->Speed += 100.f;
	bPickup = true;
	GetWorldTimerManager().ClearTimer(DelayTimer);
}

