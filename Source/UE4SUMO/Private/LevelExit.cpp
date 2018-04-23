// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelExit.h"


// Sets default values
ALevelExit::ALevelExit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WorldStaticRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = WorldStaticRoot;

	WorldStaticBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WorldStaticBox"));
	WorldStaticBox->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	WorldStaticBox->SetupAttachment(WorldStaticRoot);

}

// Called when the game starts or when spawned
void ALevelExit::BeginPlay()
{
	Super::BeginPlay();
	
	WorldStaticBox->OnComponentBeginOverlap.AddDynamic(this, &ALevelExit::OnPlayerOverlap);
}

// Called every frame
void ALevelExit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelExit::OnPlayerOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		UE_LOG(LogTemp,Warning, TEXT("Player stepped on this Collision Box"))
	}
}

