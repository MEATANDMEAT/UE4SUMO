// Fill out your copyright notice in the Description page of Project Settings.

#include "Customer.h"


// Sets default values
ACustomer::ACustomer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	GetMesh()->SetWorldScale3D(FVector(FMath::RandRange(1.f, 2.f)));
	CustomerSize = FMath::RandRange(40.f, 90.f);
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomer::OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	if (PlayerCharacter)
	{
	
		if (CustomerSize > PlayerCharacter->PlayerSize)
		{
			FRotator LungeDirection = PlayerCharacter->GetMesh()->GetComponentRotation();
			LungeDirection += FRotator(0.f, 90.f, 0.f);
			const FVector LungeVelocity = LungeDirection.Vector();
			PlayerCharacter->LaunchCharacter((LungeVelocity * 3000.f)*-1.f, true, false);
			UE_LOG(LogTemp, Warning, TEXT("Customer: %f | Player %f"), CustomerSize, PlayerCharacter->PlayerSize);
		}		
		else if (CustomerSize < PlayerCharacter->PlayerSize)
		{
			GetWorldTimerManager().SetTimer(Timer, this, &ACustomer::OnRagdoll, 1.f, true, 0.f);	
		}
	}
}

void ACustomer::OnRagdoll()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ACustomer_AI_Controller* Controller = Cast<ACustomer_AI_Controller>(GetController());
	Repeats++;
	if (Repeats < 6)
	{
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->WakeAllRigidBodies();

		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		Controller->StopMovement();
		Controller->PrimaryActorTick.bCanEverTick = false;
		Controller->StopMovement();

		UE_LOG(LogTemp, Warning, TEXT("RAGDOLL GOING"));
	} else if (Repeats > 6)
	{
		GetCapsuleComponent()->SetWorldLocation(GetMesh()->GetComponentLocation()+FVector(0.f,0.f,1.f));

		GetMesh()->PutAllRigidBodiesToSleep();
		GetMesh()->SetSimulatePhysics(false);

		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

		GetMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetComponentLocation().Z * -1));
		GetMesh()->SetRelativeRotation(FRotator(0.f,-90.f,0.f));

		Controller->PrimaryActorTick.bCanEverTick = true;
		Controller->bMoveToIsRunning = false;
		Controller->bRandomPointGenerated = false;

		Repeats = 0;
		GetWorldTimerManager().ClearTimer(Timer);

		UE_LOG(LogTemp, Warning, TEXT("RAGDOLL DONE"));
	}
}

