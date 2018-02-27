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
	posX = GetActorLocation().X / 100.f;
	posY = GetActorLocation().Y / 100.f;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::Move(){
	if (!bMoving) {
		Trace(); 
	if (bSeesPlayer){
		if (GetActorLocation().X > playerDistance) posX++;
		if (GetActorLocation().Y > playerDistance) posY++;
	}
	else {
	bool test = (Trace())?true:false;
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
		}

		bMoving = true;
	}

	else {
			SetActorLocation(FVector(100*posX, 100*posY, 100));
		bMoving = false;
	}
}

bool AEnemy::Trace(){
	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true);

	FHitResult HitOut = FHitResult(0);
	FVector End;
	End.X = posX * 1000.f;
	End.Y = posY * 1000.f;
	End.Z = 100.f;
	GetWorld()->LineTraceSingleByObjectType(
	HitOut,
	GetActorLocation(),
	End,
	ECC_WorldStatic,
	TraceParams
	);

	//if(HitOut.IsValidBlockingHit())
	//if (HitOut.Actor->HasActivePawnControlCameraComponent()){ bSeesPlayer=true; playerDistance = HitOut.Distance;}
	
	//else bSeesPlayer=false;

	if (HitOut.IsValidBlockingHit()){
	if (HitOut.Distance<100) return true;
	else return false;
	}
}