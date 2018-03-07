// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	//MeshComponent->SetupAttachment(RootComponent);
	// We want to use a spring arm to create a natual motion for our camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-50.f, 45.f, 0.f));
	SpringArm->TargetArmLength = 500.0f;
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
}

void APlayerCharacter::MoveForward(float MoveAmount)
{
	if (Controller && MoveAmount)
	{
		AddMovementInput(GetActorForwardVector(), MoveAmount);
	}
}

void APlayerCharacter::MoveRight(float MoveAmount)
{
	if (Controller && MoveAmount)
	{
		AddMovementInput(GetActorRightVector(), MoveAmount);
	}
}

//bool APlayerCharacter::Object(FVector myVector)
//{
//	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true);
//
//	FHitResult HitOut = FHitResult(0);
//	FVector End = GetActorLocation() + GetActorForwardVector()+100.f;
//	GetWorld()->LineTraceSingleByObjectType(
//		HitOut,
//		GetActorLocation(),
//		End,
//		ECC_WorldStatic,
//		TraceParams
//	);
//	if (HitOut.IsValidBlockingHit()) { UE_LOG(LogTemp, Warning, TEXT("PLAYER_COLLIDING")); }
//	else { UE_LOG(LogTemp, Warning, TEXT("PLAYER_NOT_COLLIDING")); }
//	return (HitOut.IsValidBlockingHit());
//	return true;
//}

