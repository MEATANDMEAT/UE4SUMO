// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 350.f, 0.f);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnPlayerOverlap);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacter::OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerCharacter && PlayerController) 
	{
		PlayerCharacter->DisableInput(PlayerController);
		PlayerCharacter->GetMesh()->ToggleVisibility();
		GetController()->PrimaryActorTick.bCanEverTick = false;
	}
}	