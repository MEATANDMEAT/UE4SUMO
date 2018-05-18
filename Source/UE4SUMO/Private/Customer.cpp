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
	Size = FMath::RandRange(1.f, 1.2f);
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
		if (Size > PlayerCharacter->Size)
		{
			FRotator LungeDirection = PlayerCharacter->GetMesh()->GetComponentRotation();
			LungeDirection += FRotator(0.f, 90.f, 0.f);
			const FVector LungeVelocity = LungeDirection.Vector();
			PlayerCharacter->LaunchCharacter((LungeVelocity * 1000) * -1, true, true);
			
		}
		else if (Size <= PlayerCharacter->Size && PlayerCharacter->GetCharacterMovement()->Velocity.Size() != 0.f)
		{
			if (!bFallPlaying)
			{
				GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
				GetMesh()->PlayAnimation(FallAnimation, false);
				bFallPlaying = true;
			}
			Controller->StopMovement();
			Controller->PrimaryActorTick.bCanEverTick = false;
			GetWorldTimerManager().SetTimer(Timer, this, &ACustomer::OnFall, 0.5f, true, 0.f);
		}
	}
}

void ACustomer::OnFall()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ACustomer_AI_Controller* Controller = Cast<ACustomer_AI_Controller>(GetController());

	if (Repeats < 10)
	{
		Repeats++;
		Controller->StopMovement();
		Controller->PrimaryActorTick.bCanEverTick = false;
		bUseControllerRotationPitch = true;
		bUseControllerRotationRoll = true;
		bUseControllerRotationYaw = true;

	} else if (Repeats >= 10)
	{
		Controller->PrimaryActorTick.bCanEverTick = true;
		Controller->bMoveToIsRunning = false;
		Controller->bRandomPointGenerated = false;
		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll = false;
		bUseControllerRotationYaw = false;
		Repeats = 0;
		bFallPlaying = false;
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimation(DefaultAnimation);
		GetWorldTimerManager().ClearTimer(Timer);

	}
}

