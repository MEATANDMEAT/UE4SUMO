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
}

void AEnemyCharacter::OnPlayerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	USUMOGameInstance* GameInstance = Cast<USUMOGameInstance>(GetGameInstance());
	if (PlayerCharacter && PlayerController && !PlayerCharacter->bPlayerRage && !bOnGround && GameInstance->PlayerLives > 1 && PlayerCharacter->TimerSeconds > 1)
	{
		PlayerCharacter->DisableInput(PlayerController);
		PlayerCharacter->GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		if (!PlayerCharacter->bKnockedOut)
		{
			PlayerCharacter->GetMesh()->PlayAnimation(PlayerCharacter->KnockedOutAnimation, false);
			PlayerCharacter->bKnockedOut = true;
			GetWorldTimerManager().SetTimer(PlayerCharacter->CaughtTimer, PlayerCharacter, &APlayerCharacter::Caught, 1.0, true, 0.f);
			UGameplayStatics::PlaySound2D(GetWorld(), PlayerCharacter->DefeatSound, 1.f, 1.f);
		}
	}
	else if (PlayerCharacter && PlayerController && PlayerCharacter->bPlayerRage)
	{
		if (!bFallPlaying)
		{
			GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			GetMesh()->PlayAnimation(FallAnimation, false);
			bFallPlaying = true;
		}
		GetWorldTimerManager().SetTimer(RageTimer, this, &AEnemyCharacter::OnPlayerRage, 0.2f, true, 0.f);
		bOnGround = true;
	}
	else if (PlayerCharacter && PlayerController && GameInstance->PlayerLives <= 1 && PlayerCharacter->TimerSeconds > 1)
	{
		PlayerCharacter->DisableInput(PlayerController);
		PlayerCharacter->GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		PlayerCharacter->GetMesh()->PlayAnimation(PlayerCharacter->KnockedOutAnimation, false);
		GameInstance->PlayerLives = 0;
		PlayerCharacter->bShowGameOver = true;
		GetWorldTimerManager().PauseTimer(PlayerCharacter->LevelTimerHandle);
	}
}

void AEnemyCharacter::OnPlayerRage()
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AEmployees_AI_Controller* Controller = Cast<AEmployees_AI_Controller>(GetController());
	if (FunctionRepeats < 30)
	{
		FunctionRepeats++;
		Controller->StopMovement();
		Controller->PrimaryActorTick.bCanEverTick = false;
		Controller->bIsPlayerDetected = false;
		Controller->bAIRemember = false;
	}
	else if (FunctionRepeats >= 30)
	{
		bFallPlaying = false;
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimation(DefaultAnimation);
		Controller->PrimaryActorTick.bCanEverTick = true;
		Controller->bMoveToIsRunning = false;
		Controller->bRandomPointGenerated = false;
		bOnGround = false;
		FunctionRepeats = 0;
		GetWorldTimerManager().ClearTimer(RageTimer);
	}
}
