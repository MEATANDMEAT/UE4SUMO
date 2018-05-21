// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4SUMOGameModeBase.h"

void AUE4SUMOGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (UGameplayStatics::GetCurrentLevelName(GetWorld(), true) != FString("Main"))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Music, 1.f, 1.f, 0.f, nullptr, nullptr);
	}
}

void AUE4SUMOGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
