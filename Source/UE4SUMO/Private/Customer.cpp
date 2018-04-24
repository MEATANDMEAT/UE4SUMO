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
	GetMesh()->SetWorldScale3D(FVector(FMath::RandRange(1.f, 1.8f)));
	CustomerSize = FMath::RandRange(40.f, 90.f);
}

// Called every frame
void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMesh()->SetWorldRotation(FMath::Lerp(FQuat(GetMesh()->GetComponentRotation()), FQuat(FRotator(GetRootComponent()->GetComponentRotation().Pitch, GetRootComponent()->GetComponentRotation().Yaw - 90.f, FallRotation)), 5.f * DeltaTime));
}

void ACustomer::OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	if (PlayerCharacter)
	{
	
		if (GetMesh()->GetComponentScale().Size() > PlayerCharacter->GetMesh()->GetComponentScale().Size())
		{
			FRotator LungeDirection = PlayerCharacter->GetMesh()->GetComponentRotation();
			LungeDirection += FRotator(0.f, 90.f, 0.f);
			const FVector LungeVelocity = LungeDirection.Vector();
			PlayerCharacter->LaunchCharacter((LungeVelocity * 5000.f)*-1.f, true, false);
			UE_LOG(LogTemp, Warning, TEXT("Customer: %f | Player %f"), CustomerSize, PlayerCharacter->PlayerSize);
		}		
		else if (GetMesh()->GetComponentScale().Size() < PlayerCharacter->GetMesh()->GetComponentScale().Size() && PlayerCharacter->GetCharacterMovement()->Velocity.Size() != 0.f)
		{
			FallRotation = -90.f;
			GetWorldTimerManager().SetTimer(Timer, this, &ACustomer::OnRagdoll, 0.5f, true, 0.f);	
		}
	}
}

void ACustomer::OnRagdoll()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ACustomer_AI_Controller* Controller = Cast<ACustomer_AI_Controller>(GetController());

	if (Repeats < 10)
	{
		Repeats++;
		Controller->StopMovement();
		Controller->PrimaryActorTick.bCanEverTick = false;
		Controller->StopMovement();
		 
		UE_LOG(LogTemp, Warning, TEXT("Customer on the ground"));

	} else if (Repeats >= 10)
	{
		//UE_LOG(LogTemp, Warning, TEXT("MeshRotation before: %s"),*GetMesh()->GetComponentRotation().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("ColliderRotation before: %s"), *GetCapsuleComponent()->GetComponentRotation().ToString());
		FallRotation = 0.f;
		Controller->PrimaryActorTick.bCanEverTick = true;
		Controller->bMoveToIsRunning = false;
		Controller->bRandomPointGenerated = false;

		Repeats = 0;
		//UE_LOG(LogTemp, Warning, TEXT("MeshRotation after: %s"), *GetMesh()->GetComponentRotation().ToString());
		//UE_LOG(LogTemp, Warning, TEXT("ColliderRotation after: %s"), *GetCapsuleComponent()->GetComponentRotation().ToString());
		GetWorldTimerManager().ClearTimer(Timer);

		UE_LOG(LogTemp, Warning, TEXT("Customer got back up"));
	}
}

