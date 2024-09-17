// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "InputAction.h"

#include "Input_ConfigData.generated.h"

UCLASS()
class RTSGAME_API UInput_ConfigData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Pointer to the forward/backwards player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* MoveXInput = nullptr;

	// Pointer to the strafe player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Inputs")
	class UInputAction* MoveYInput = nullptr;

	// Pointer to the camera rotation player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Inputs")
	class UInputAction* RotateCamera = nullptr;

	// Pointer to the modify camrera zoom player input
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Inputs")
	class UInputAction* ZoomCamera = nullptr;	
};
