// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuController.h"

AMenuController::AMenuController() 
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(RootComponent);
	
}

void AMenuController::BeginPlay() 
{
	Super::BeginPlay();
	MyMainMenu = CreateWidget<UUserWidget>(this, MainMenu);
	MyMainMenu->AddToViewport();
	bShowMouseCursor = true;

}

FString AMenuController::GetPrimaryGPUBrand()
{
	return FGenericPlatformMisc::GetPrimaryGPUBrand();
}

FString AMenuController::GetCPUBrand()
{
	return FGenericPlatformMisc::GetCPUVendor();
}
