// Fill out your copyright notice in the Description page of Project Settings.
#include "PawnCharacter.h"
#define OUT

// Sets default values
APawnCharacter::APawnCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// We initialize our Mesh and Root components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	// We want to use a spring arm to create a natual motion for our camera.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation (FRotator(-50.f, 45.f, 0.f));
	SpringArm->TargetArmLength = 500.0f;
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
	// Each X second, we set PlayerCanMove to true
}

// Called every frame
void APawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
//	timeSinceMoved+=DeltaTime;
//	if (timeSinceMoved > 0.3f) { PlayerCanMove = true; MOVEMENT = FVector(NULL, NULL, NULL); }
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), GetActorForwardVector(), DeltaTime, 1.33333f));
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

void APawnCharacter::MoveUp()
{
	// We check if PlayerCanMove and if there is an object in front,  
	if (PlayerCanMove && !Object(MOVE_UP))
	{
		// Add animation here
		MOVEMENT = MOVE_UP;
		UE_LOG(LogTemp, Warning, TEXT("MOVE_UP"))
			timeSinceMoved = 0.f;
		PlayerCanMove = false;
	}
}
void APawnCharacter::MoveDown()
{
	if (PlayerCanMove && !Object(MOVE_DOWN))
	{
		MOVEMENT = MOVE_DOWN;
		UE_LOG(LogTemp, Warning, TEXT("MOVE_DOWN"))
			timeSinceMoved = 0.f;
		PlayerCanMove = false;
	}
}
void APawnCharacter::MoveRight()
{
	if (PlayerCanMove && !Object(MOVE_RIGHT))
	{
		MOVEMENT = MOVE_RIGHT;
		UE_LOG(LogTemp, Warning, TEXT("MOVE_LEFT"))
			timeSinceMoved = 0.f;
		PlayerCanMove = false;
	}
}
void APawnCharacter::MoveLeft()
{
	if (PlayerCanMove && !Object(MOVE_LEFT))
	{
		MOVEMENT = MOVE_LEFT;
		UE_LOG(LogTemp, Warning, TEXT("MOVE_RIGHT"))
			timeSinceMoved = 0.f;
		PlayerCanMove = false;
	}
}
/// Ray Trace to see if Player Pawn collides with static geometry. 
bool APawnCharacter::Object(FVector Direction) 
{
	FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true);

	FHitResult HitOut = FHitResult(0);
	FVector End = GetActorLocation() + Direction;
	GetWorld()->LineTraceSingleByObjectType(
		HitOut,
		GetActorLocation(),
		End,
		ECC_WorldStatic,
		TraceParams
	);
	if (HitOut.IsValidBlockingHit()) { UE_LOG(LogTemp, Warning, TEXT("PLAYER_COLLIDING")); }
	else { UE_LOG(LogTemp, Warning, TEXT("PLAYER_NOT_COLLIDING")); }
	return (HitOut.IsValidBlockingHit());
}

void APawnCharacter::Destroyed(){
	UE_LOG(LogTemp, Warning, TEXT("You got caught by a store employee--Game Over!"));
}