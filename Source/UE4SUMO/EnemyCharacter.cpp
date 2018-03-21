// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	EnemyState = EAIState::Patrolling;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnPlayerOverlap);
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AEnemyCharacter::OnNoiseHear);
}

void AEnemyCharacter::OnPawnSeen(APawn * SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("AI Saw Something!"));
	EnemyState = EAIState::Alerted;
}

void AEnemyCharacter::OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("AI Heard Something!"));
	EnemyState = EAIState::Suspicous;
}

void AEnemyCharacter::SetGuardState(EAIState NewState)
{
	if (EnemyState == NewState)
		return;
	EnemyState = NewState;
	OnStateChanged(EnemyState);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("Hit something"))
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter) {
		UE_LOG(LogTemp, Error, TEXT("Hitting player!"))
		 OtherActor->Destroy();
	}
}	