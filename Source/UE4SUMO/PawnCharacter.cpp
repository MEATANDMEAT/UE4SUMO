// Fill out your copyright notice in the Description page of Project Settings.
#include "PawnCharacter.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"


// Sets default values
APawnCharacter::APawnCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// We initialize our Mesh and Root components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	// We want to use a spring arm to create a natual motion for our camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 900.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 8.0f;

	// Now we create a camera and attach to our spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	// Last, we take control of the first default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APawnCharacter::BeginPlay()
{
	Super::BeginPlay();
	//SpringArm->SetRelativeTransform(CameraTransform);
}

// Called every frame
void APawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// We set up movement for our pawn actor
	InputComponent->BindAction("MoveUp", IE_Pressed, this, &APawnCharacter::MoveUp);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &APawnCharacter::MoveDown);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &APawnCharacter::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &APawnCharacter::MoveLeft);
	InputComponent->BindAction("MoveUp", IE_Released, this, &APawnCharacter::Release);
	InputComponent->BindAction("MoveDown", IE_Released, this, &APawnCharacter::Release);
	InputComponent->BindAction("MoveRight", IE_Released, this, &APawnCharacter::Release);
	InputComponent->BindAction("MoveLeft", IE_Released, this, &APawnCharacter::Release);

}
void APawnCharacter::MoveUp()
{
		AddActorLocalOffset(MOVE_UP, false);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_UP"))
	
}
void APawnCharacter::MoveDown()
{
		AddActorLocalOffset(MOVE_DOWN, false);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_DOWN"))
}
void APawnCharacter::MoveRight()
{
		AddActorLocalOffset(MOVE_RIGHT, false);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_RIGHT"))
}
void APawnCharacter::MoveLeft()
{
		AddActorLocalOffset(MOVE_LEFT, false);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_LEFT"))
}
void APawnCharacter::Release()
{
	Pressed = false;  
}
