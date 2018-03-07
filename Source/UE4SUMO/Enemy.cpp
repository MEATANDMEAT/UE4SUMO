// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = false;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent")); 
	////EnemyMesh->SetupAttachment(RootComponent);
	//EnemyMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	//EnemyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyBox"));
	//EnemyBox->SetWorldScale3D(FVector(1.5f, 1.5f, 2.5f));
	//EnemyBox->bGenerateOverlapEvents = true;
	//EnemyBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnEnemyHitPawn);
	//EnemyBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
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

void AEnemy::Move()
{
	if (!bMoving) {
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

		bMoving = true;
	}
	else 
	{
		SetActorLocation(FVector(100*posX, 100*posY, 100));
		bMoving = false;
	}
}

bool AEnemy::Trace()
{
	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true);
	FVector End;
	End.X = posX * 100.f;
	End.Y = posY * 100.f;
	End.Z = 100.f;	
	GetWorld()->LineTraceSingleByObjectType(
	HitOut,
	GetActorLocation(),
	End,
	ECC_WorldStatic,
	TraceParams
	);
	return HitOut.bBlockingHit;
}
void AEnemy::OnEnemyHitPawn(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->GetName().Contains(TEXT("PawnCharacter"))) {
		TArray<UStaticMeshComponent*> Comps;
		OtherActor->GetComponents(Comps);
		if (Comps.Num() > 0) {
			UStaticMeshComponent* FoundComp = Comps[0];
		}
		FVector Size = Comps[0]->GetComponentScale();
		if (Size.X<1.2) OtherActor->Destroy();
		else Destroy();
	}
}