// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// We want to use a spring arm to create a natual motion for our camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-50.f, 45.f, 0.f));
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 8.0f;

	// Now we create a camera and attach to our spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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
	FRotator CurrentRotation = GetMesh()->GetComponentRotation();  //the rotation of the guard right now
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
}

void APlayerCharacter::MoveForward(float MoveAmount)
{
	if (Controller)
	{
		if (MoveAmount > 0)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
			RotationValue = 0.f, -90.f, 0.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorForwardVector(), MoveAmount);
		}
		else if (MoveAmount < 0)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
			RotationValue = 0.f, 90.f, 0.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorForwardVector(), MoveAmount);
		}
	}
}

void APlayerCharacter::MoveRight(float MoveAmount)
{
	if (Controller)
	{
		if (MoveAmount > 0)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
			RotationValue = 0.f, 0.f, 0.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorRightVector(), MoveAmount);
		}
		else if (MoveAmount < 0)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
			RotationValue = 0.f, -180.f, 0.f;
			FRotator CurrentRotation = GetMesh()->GetComponentRotation();
			GetMesh()->SetRelativeRotation(FMath::Lerp(FQuat(CurrentRotation), FQuat(FRotator(0.0f, RotationValue, 0.0f)), LerpSteps));
			AddMovementInput(GetActorRightVector(), MoveAmount);
		}
	}
}

void APlayerCharacter::Run(float RunSpeed)
{
	if (Controller&&RunSpeed)
	{
		Cast<UCharacterMovementComponent>(GetCharacterMovement())->MaxWalkSpeed = Speed * 1.6;
		UE_LOG(LogTemp, Warning, TEXT("YOU ARE RUNNING"))
	}
	else Cast<UCharacterMovementComponent>(GetCharacterMovement())->MaxWalkSpeed = Speed;
}

void APlayerCharacter::Eat(float SizeIncrease) {
	Size+=SizeIncrease;
	GetMesh()->SetWorldScale3D(FVector(Curve->GetFloatValue(Size-1.f)));
	Speed -= 100.f * SizeIncrease;
}