// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelExit.h"


// Sets default values
ALevelExit::ALevelExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = Root;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	Box->bGenerateOverlapEvents = true;
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALevelExit::OnPlayerEnterPickupBox);
	Box->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ALevelExit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelExit::OnPlayerEnterPickupBox(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter && !PlayerCharacter->bChiliPickup)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), OverlapSound, 0.2f, 1, 0, nullptr, PlayerCharacter);
		if (PlayerCharacter->Score >= ScoreNeeded) PlayerCharacter->bShowRoundEnd = true;
		else PlayerCharacter->bNotEnoughScoreText = true;
	}
}

