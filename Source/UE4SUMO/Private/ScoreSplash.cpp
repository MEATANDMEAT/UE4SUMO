// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreSplash.h"


// Sets default values
AScoreSplash::AScoreSplash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Score = CreateDefaultSubobject<UBillboardComponent>(TEXT("Score"));
	Score->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AScoreSplash::BeginPlay()
{
	Super::BeginPlay();
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	SetActorLocation(FVector(Player->GetActorLocation().X, Player->GetActorLocation().Y, (Player->GetActorLocation().Z * 2)+10));
	GetWorldTimerManager().SetTimer(Timer, this, &AScoreSplash::OnTimerEnd, 1.f, true, 0.f);
}

// Called every frame
void AScoreSplash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRelativeLocation(GetActorLocation()+FVector(0.f, 0.f, 50.f * DeltaTime));
}

void AScoreSplash::OnTimerEnd()
{
	if (Seconds > 0)
	{
		Seconds--;
	}
	else if (Seconds <= 0)
	{
		Destroy();
	}
}
