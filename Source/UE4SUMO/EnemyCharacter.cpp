// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemyCharacter::OnEnemyHitPlayer(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerCharacter *PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	TArray<USkeletalMeshComponent*> Comps;
	if (PlayerCharacter) {
		OtherActor->GetComponents(Comps);
		if (Comps.Num() > 0) {
			USkeletalMeshComponent* FoundComp = Comps[0];
		}
		FVector Size = Comps[0]->GetComponentScale();
		if (Size.X<1.2) OtherActor->Destroy();
		else Destroy();
	}
}
