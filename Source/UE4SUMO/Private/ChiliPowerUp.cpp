// Fill out your copyright notice in the Description page of Project Settings.

#include "ChiliPowerUp.h"


// Sets default values
AChiliPowerUp::AChiliPowerUp()
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
	Box->OnComponentBeginOverlap.AddDynamic(this, &AChiliPowerUp::OnPlayerEnterPickupBox);
	Box->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AChiliPowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChiliPowerUp::Tick(float DeltaTime)
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

void AChiliPowerUp::OnPlayerEnterPickupBox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (PlayerCharacter && !bPickup && !PlayerCharacter->bChiliPickup)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AChiliPowerUp::PlayerRage, 1.f, true, 0.f);
		UGameplayStatics::PlaySound2D(GetWorld(), SpeedBoostSound, 0.2f, 1, 0, nullptr, PlayerCharacter);
		PlayerCharacter->bChiliPickup = true;
		bPickup = true;
	}
}

void AChiliPowerUp::PlayerRage()
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Repeats--;
	if (Repeats > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player in rage!"), Repeats)
	}
	else if (Repeats <= 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("Player now calm"))
		PlayerCharacter->bChiliPickup = false;
		Destroy();
	}

}


