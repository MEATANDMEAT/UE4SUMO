// Fill out your copyright notice in the Description page of Project Settings.
#include "PawnCharacter.h"
#define OUT

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
	// Each 0.8 second, we set PlayerCanMove to true
	GetWorldTimerManager().SetTimer(MovementHandle, this, &APawnCharacter::Movement, 0.8f,true);
}

// Called every frame
void APawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// We set up movement for our pawn actor
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("MoveUp", IE_Pressed, this, &APawnCharacter::MoveUp);
	InputComponent->BindAction("MoveDown", IE_Pressed, this, &APawnCharacter::MoveDown);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &APawnCharacter::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &APawnCharacter::MoveLeft);
}
void APawnCharacter::Movement()
{
	// We set PlayerCanMove to true since we want the player to be able to move at the start
	PlayerCanMove = true;
UE_LOG(LogTemp,Error,TEXT("Player can move!"))
}
void APawnCharacter::MoveUp()
{
	// We check if PlayerCanMove is true, if it is we move the actor and then set PlayerCanMove to false
	// We create 
	if (PlayerCanMove == true && !RayTrace(FVector(100.f, 0.f, 0.f)))
	{
		// Add animation here
		AddActorLocalOffset(MOVE_UP, true);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_UP"))
		PlayerCanMove = false;
	}
}
void APawnCharacter::MoveDown()
{
	if (PlayerCanMove == true && !RayTrace(FVector(-100.f, 0.f, 0.f)))
	{
		AddActorLocalOffset(MOVE_DOWN, true);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_DOWN"))
		PlayerCanMove = false;
	}
}
void APawnCharacter::MoveRight()
{
	if (PlayerCanMove == true && !RayTrace(FVector(0.f, -100.f, 0.f)))
	{
		AddActorLocalOffset(MOVE_RIGHT, true);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_RIGHT"))
		PlayerCanMove = false;
	}
}
void APawnCharacter::MoveLeft()
{
	if (PlayerCanMove == true && !RayTrace(FVector(0.f, 100.f, 0.f)))
	{
		AddActorLocalOffset(MOVE_LEFT, true);
		UE_LOG(LogTemp, Warning, TEXT("MOVE_LEFT"))
		PlayerCanMove = false;
	}
}
bool APawnCharacter::RayTrace(FVector myVector) {
	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = false;
	FHitResult HitOut = FHitResult(ForceInit);
	FVector End = GetActorLocation() + myVector;
	GetWorld()->LineTraceSingleByObjectType(
		HitOut,
		GetActorLocation(),
		End,
		ECC_PhysicsBody,
		TraceParams
	);
	if (HitOut.IsValidBlockingHit()) { UE_LOG(LogTemp, Warning, TEXT("HIT")); }
	else { UE_LOG(LogTemp, Warning, TEXT("MISS")); }
	return (HitOut.IsValidBlockingHit());
}