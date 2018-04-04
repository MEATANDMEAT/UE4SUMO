// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnPawnSeen);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AEnemyCharacter::OnNoiseHear);
	}
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnPlayerOverlap);
}

void AEnemyCharacter::OnPawnSeen(APawn * SeenPawn)
{
	AEmployees_AI_Controller* AIController = Cast<AEmployees_AI_Controller>(GetController());
	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComp();
	if (PawnSensingComp->CouldSeePawn(SeenPawn, false) && AIController)
	{
		AIController->SetPlayerSeen(SeenPawn);
		BlackboardComp->SetValueAsObject(AIController->PlayerKey, SeenPawn);
		UE_LOG(LogTemp, Warning, TEXT("AI Saw Something!"));
	}
	else if (!(PawnSensingComp->CouldSeePawn(SeenPawn, false)))
	{
		UE_LOG(LogTemp, Warning, TEXT("AI no longer sees anything"));
	}
	
}

void AEnemyCharacter::OnNoiseHear(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("AI Heard Something!"));
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