// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// We want to use a spring arm to create a natual motion for our camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-50.f, 45.f, 0.f));
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 8.0f;

	// Now we create a camera and attach to our spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	LerpSteps = 0.05f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	RotationValue = -90.f;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator CurrentRotation = GetMesh()->GetComponentRotation();  //the rotation of the enemy right now
										   //we will use only yaw (the y-axis)       
	GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAxis("Run", this, &APlayerCharacter::Run);
	InputComponent->BindAxis("LungeCharge", this, &APlayerCharacter::LungeCharge);
	InputComponent->BindAction("Lunge", IE_Released, this, &APlayerCharacter::LungeRelease);
}

void APlayerCharacter::MoveForward(float MoveAmount)
{
	if (Controller)
	{
		if (MoveAmount > 0)
		{
			RotationValue = -90.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorForwardVector(), MoveAmount);
			PawnMakeNoise(1.f, GetActorLocation(), false);
		}
		else if (MoveAmount < 0)
		{
			RotationValue = 90.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorForwardVector(), MoveAmount);
			PawnMakeNoise(1.f, GetActorLocation(), false);
		}
	}
}

void APlayerCharacter::MoveRight(float MoveAmount)
{
	if (Controller)
	{
		if (MoveAmount > 0)
		{
			//GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
			RotationValue = 0.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorRightVector(), MoveAmount);
			PawnMakeNoise(1.f, GetActorLocation(), false);
		}
		else if (MoveAmount < 0)
		{
			//GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
			RotationValue = -180.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorRightVector(), MoveAmount);
			PawnMakeNoise(1.f, GetActorLocation(), false);
		}
	}
}

void APlayerCharacter::Run(float RunSpeed)
{
	if (Controller&&RunSpeed)
	{
		Cast<UCharacterMovementComponent>(GetCharacterMovement())->MaxWalkSpeed = Speed * 1.6;
		TArray<USkeletalMeshComponent*> Comps;
			GetComponents(Comps);
			if (Comps.Num() > 0)
			{
				USkeletalMeshComponent* FoundComp = Comps[0];
				Comps[0]->SetWorldScale3D(Comps[0]->GetComponentScale() + -0.0005f);
			}
			Speed += 0.1f;
	}
	else Cast<UCharacterMovementComponent>(GetCharacterMovement())->MaxWalkSpeed = Speed;
}

void APlayerCharacter::LungeCharge(float Charge)
{
	if (Controller && Charge)
	{
		LungeAttackCharge += 25.f;
		UE_LOG(LogTemp,Warning,TEXT("Charging the attack: %f"),LungeAttackCharge)
	}
}

void APlayerCharacter::LungeRelease()
{
	FRotator LungeDirection = GetMesh()->GetComponentRotation();
	LungeDirection += FRotator(0.f, 90.f, 0.f);
	FVector LungeVelocity = LungeDirection.Vector() * LungeAttackCharge;
	this->LaunchCharacter(LungeVelocity, true, true);
	LungeAttackCharge = 0.f;
}


