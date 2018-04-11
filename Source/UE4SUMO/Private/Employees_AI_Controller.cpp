// Fill out your copyright notice in the Description page of Project Settings.

#include "Employees_AI_Controller.h"

// Sets default values
AEmployees_AI_Controller::AEmployees_AI_Controller(){
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NavSys = UNavigationSystem::GetCurrent(GetWorld());
	AIState = 0;
	Target = NavSys->GetRandomPointInNavigableRadius(GetWorld(), GetPawn()->GetActorLocation(), 2000.f);
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

// Called when the game starts or when spawned
void AEmployees_AI_Controller::BeginPlay(){
	Super::BeginPlay();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEmployees_AI_Controller::OnPawnSeen);
	
}

// Called every frame
void AEmployees_AI_Controller::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	switch (AIState){
		case 0: //Moving randomly
		case 1: //Moving to last seen location
			if ((GetPawn()->GetActorLocation()) == Target) {
				Target = NavSys->GetRandomPointInNavigableRadius(GetWorld(), GetPawn()->GetActorLocation(), 2000.f);
				AIState = 0;
			}
		break;
		case 2: //Chasing player
		break;
	}
	MoveToLocation(Target, -1.f, false);
	
}

void AEmployees_AI_Controller::OnPawnSeen(APawn * SeenPawn){
	Target = SeenPawn->GetActorLocation();
	AIState = 2;
}