// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 350.f, 0.f);

	Exclaimation = CreateDefaultSubobject<UBillboardComponent>(TEXT("Exclaimation"));
	Question = CreateDefaultSubobject<UBillboardComponent>(TEXT("Question"));
	Exclaimation->SetupAttachment(RootComponent);
	Question->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Exclaimation->SetHiddenInGame(true);
	Question->SetHiddenInGame(true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnPlayerOverlap);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetMesh()->SetWorldRotation(FMath::Lerp(FQuat(GetMesh()->GetComponentRotation()), FQuat(FRotator(GetRootComponent()->GetComponentRotation().Pitch, GetRootComponent()->GetComponentRotation().Yaw - 90.f, FallRotation)), 5.f * DeltaTime));
}

void AEnemyCharacter::OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerCharacter && PlayerController && !PlayerCharacter->bPlayerRage && !bOnGround)
	{
		PlayerCharacter->DisableInput(PlayerController);
		PlayerCharacter->GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		PlayerCharacter->GetMesh()->PlayAnimation(PlayerCharacter->KnockedOutAnimation, false);
		PlayerCharacter->bKnockedOut = true;
		GetWorldTimerManager().SetTimer(PlayerCharacter->CaughtTimer, PlayerCharacter, &APlayerCharacter::Caught, 1.0, true, 0.f);
	}
	else if (PlayerCharacter && PlayerController && PlayerCharacter->bPlayerRage)
	{
		FallRotation = -90.f;
		GetWorldTimerManager().SetTimer(RageTimer, this, &AEnemyCharacter::OnPlayerRage, 0.2f, true, 0.f);
		PlayerCharacter->bPunch = true;
		bOnGround = true;
	}
}

void AEnemyCharacter::OnPlayerRage()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AEmployees_AI_Controller* Controller = Cast<AEmployees_AI_Controller>(GetController());
	if (FunctionRepeats < 50)
	{
		FunctionRepeats++;
		Controller->StopMovement();
		Controller->PrimaryActorTick.bCanEverTick = false;
		Controller->bIsPlayerDetected = false;
		Controller->bAIRemember = false;


	}
	else if (FunctionRepeats >= 50)
	{
		FallRotation = 0.f;

		Controller->PrimaryActorTick.bCanEverTick = true;
		Controller->bMoveToIsRunning = false;
		Controller->bRandomPointGenerated = false;
		bOnGround = false;
		FunctionRepeats = 0;
		GetWorldTimerManager().ClearTimer(RageTimer);
	}
}
