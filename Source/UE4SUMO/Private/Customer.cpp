// Fill out your copyright notice in the Description page of Project Settings.

#include "Customer.h"


// Sets default values
ACustomer::ACustomer()
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
void ACustomer::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACustomer::OnPlayerOverlap);
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomer::OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("COLLIDING!"))
		PlayerCharacter->LaunchCharacter((PlayerCharacter->GetMesh()->GetForwardVector() *-1.f)*3000.f, true,false);
	}
}

