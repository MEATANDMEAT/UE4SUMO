// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4SUMOGameModeBase.h"

void AUE4SUMOGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<ACustomer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		CustomerArray.push_back(ActorItr);
		UE_LOG(LogTemp, Error, TEXT("Found an actor %s"), *CustomerArray[0]->GetName());
	}

}

void AUE4SUMOGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
