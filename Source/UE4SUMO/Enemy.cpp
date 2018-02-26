// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); 

	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &AEnemy::Move, MoveTimer, true, MoveTimer+1.0f);
	posX = GetActorLocation().X;
	posY = GetActorLocation().Y;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::Move(){
	if (!bMoving) {
	bool test{false};
		test = (Trace())?true:false;
		do {
		char r = rand()%4;
		switch (r){
			case 0:
				posX++;
				test = false;
				if(Trace()){posX--; test=true;}
			break;
			case 1:
				posX--;
				test = false;
				if(Trace()){posX++; test=true;}
			break;
			case 2:
				posY++;
				test = false;
				if(Trace()){posY--; test=true;}
			break;
			case 3:
				posY--;
				test = false;
				if(Trace()){posY++; test=true;}
			break;
		}
		} while(test);

		bMoving = true;
	}

	else {
			FVector newLocation (100 * posX, 100 * posY, 100);
			SetActorLocation(newLocation);
		bMoving = false;
	}
}

bool AEnemy::Trace(){
	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;

	FHitResult HitOut = FHitResult(ForceInit);
	FVector End;
	End.X = posX * 100.f;
	End.Y = posY * 100.f;
	End.Z = 100.f;
	GetWorld()->LineTraceSingleByChannel(
	HitOut,
	GetActorLocation(),
	End,
	ECC_Pawn,
	TraceParams
	);

	return HitOut.bBlockingHit;
}