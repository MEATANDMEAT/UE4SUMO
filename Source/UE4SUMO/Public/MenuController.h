// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

/**
 *
 */
UCLASS()

class UE4SUMO_API AMenuController : public APlayerController
{
	GENERATED_BODY()

	AMenuController();

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainMenu;

	UUserWidget* MyMainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* OurCamera;

	UFUNCTION(BlueprintPure, Category = "Hardware")
		static FString GetPrimaryGPUBrand();

	UFUNCTION(BlueprintPure, Category = "Hardware")
		static FString GetCPUBrand();


};
