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
	LerpSteps = 0.075f;

	TeamId = FGenericTeamId(1);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);  
	GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(GetMesh()->GetComponentRotation()), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
	GetMesh()->SetRelativeScale3D(FMath::Lerp(FVector(GetMesh()->GetComponentScale()), FVector(Curve->GetFloatValue(Size-1.f)), 0.03f));
	UE_LOG(LogTemp,Warning,TEXT("PlayerSize %s"),*GetMesh()->GetComponentScale().ToString())
	if (bRunning == true && Size > 1.f && GetCharacterMovement()->Velocity.Size()!=0) 
	{
		Size -= 0.1f * DeltaTime;
		Speed += 5.f * DeltaTime;
		GetMesh()->SetWorldScale3D(FVector(Curve->GetFloatValue(Size - 1.f)));
	}

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
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(GetMesh()->GetComponentRotation()), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorForwardVector(), MoveAmount);
			PawnMakeNoise(1.f, GetActorLocation(), false);
		}
		else if (MoveAmount < 0)
		{
			RotationValue = 90.f;
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(GetMesh()->GetComponentRotation()), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
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
			RotationValue = 0.f;
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(GetMesh()->GetComponentRotation()), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorRightVector(), MoveAmount);
			PawnMakeNoise(1.f, GetActorLocation(), false);
		}
		else if (MoveAmount < 0)
		{
			RotationValue = -180.f;
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(GetMesh()->GetComponentRotation()), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
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
		bRunning = true;
	}
	else {
		Cast<UCharacterMovementComponent>(GetCharacterMovement())->MaxWalkSpeed = Speed;
		bRunning = false;
	}
}

void APlayerCharacter::LungeCharge(float Charge)
{
	if (Controller && Charge)
	{
		LungeAttackCharge += 50.f;
	}
}

void APlayerCharacter::LungeRelease()
{
	FRotator LungeDirection = GetMesh()->GetComponentRotation();
	LungeDirection += FRotator(0.f, 90.f, 0.f);
	FVector LungeVelocity = LungeDirection.Vector() * LungeAttackCharge;
	this->GetCharacterMovement()->AddImpulse(LungeVelocity, true);
	LungeAttackCharge = 0.f;
}


void APlayerCharacter::EatUnhealthy(float SizeIncrease) 
{
	if (Size <= 2.f) Size += SizeIncrease;
	Speed -= 50.f * SizeIncrease;
}

void APlayerCharacter::EatHealthy(float SizeDecrease)
{
	if (Size >= 1.f) Size -= SizeDecrease;
	Speed += 50.f * SizeDecrease;
}

FGenericTeamId APlayerCharacter::GetGenericTeamId() const
{
	return TeamId;
}
