// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
			GetMesh()->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
			AddMovementInput(GetActorForwardVector(), MoveAmount);
		}
		else if (MoveAmount < 0)
		{
			GetMesh()->SetWorldRotation(FRotator(0.f, 90.f, 0.f));
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
			GetMesh()->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
			AddMovementInput(GetActorRightVector(), MoveAmount);
		}
		else if (MoveAmount < 0)
		{
			GetMesh()->SetWorldRotation(FRotator(0.f, -180.f, 0.f));
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

