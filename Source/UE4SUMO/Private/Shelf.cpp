// Fill out your copyright notice in the Description page of Project Settings.

#include "Shelf.h"
//#include "Math/UnrealMathUtility.h"

// Sets default values
AShelf::AShelf() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WorldStaticRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = WorldStaticRoot;
	WorldStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorldStaticMesh"));
	WorldStaticMesh->SetupAttachment(WorldStaticRoot);

	WorldStaticBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WorldStaticBox"));
	WorldStaticBox->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	WorldStaticBox->SetupAttachment(WorldStaticRoot);
}

// Called when the game starts or when spawned
void AShelf::BeginPlay() {
	Super::BeginPlay();
	FVector Location(GetActorLocation());
	Location.Z = 150.f;
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	bAllowSpawn = FMath::RandBool();
	if (bAllowSpawn) {
		GetWorld()->SpawnActor<AFoodPickup>(Food->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(-30.f, -70.f), 0.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
		GetWorld()->SpawnActor<AFoodPickup>(Food->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(-30.f, -70.f), -100.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
		GetWorld()->SpawnActor<AFoodPickup>(Food->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(30.f, 70.f), 0.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
		GetWorld()->SpawnActor<AFoodPickup>(Food->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(30.f, 70.f), -100.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
	}
	else {
		GetWorld()->SpawnActor<AHealthyFoodPickup>(HealthyFood->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(-30.f, -70.f), 0.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
		GetWorld()->SpawnActor<AHealthyFoodPickup>(HealthyFood->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(-30.f, -70.f), -100.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
		GetWorld()->SpawnActor<AHealthyFoodPickup>(HealthyFood->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(30.f, 70.f), 0.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
		GetWorld()->SpawnActor<AHealthyFoodPickup>(HealthyFood->GetAuthoritativeClass(), Location + FVector(FMath::RandRange(-25.f, -10.f), FMath::RandRange(30.f, 70.f), -100.f).RotateAngleAxis(GetActorRotation().Yaw,FVector(0,0,1)), Rotation, SpawnInfo);
	}
}

// Called every frame
void AShelf::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

