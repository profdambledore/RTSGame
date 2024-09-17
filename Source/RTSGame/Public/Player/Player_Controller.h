// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "InputAction.h"
#include "Engine/DataAsset.h"

#include "Player_Controller.generated.h"

class APlayer_Character;

UCLASS()
class RTSGAME_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	// Constructor
	APlayer_Controller();

	// Called to setup the inputs for this player controller
	virtual void SetupInputComponent() override;

	// Called when the controller possesses a character/pawn
	virtual void OnPossess(APawn* InPawn) override;

	// Called to return a pointer to the controller character
	APlayer_Character* GetPC() { return Character; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// -- Inputs --
	// Called to move the character on the X axis
	void MoveX(const FInputActionValue& Value);

	// Called to move the character on the Y axis
	void MoveY(const FInputActionValue& Value);

	// Called to make the character's camera rotate
	void RotateCamera(const FInputActionValue& Value);

	// Called to modify the camera's zoom
	void ZoomCamera(const FInputActionValue& Value);

private:
	/// -- Utility Functions --
	// Called to return if an input value is positive or negative
	bool GetInputValueIsPositive(float InInputValue);
	
public:

protected:

private:
	/// -- Controlled Character --
	// Pointer to the character this controller possesses
	class APlayer_Character* Character = nullptr;

	/// -- Inputs --
	// Pointer to the Input Config File
	class UInput_ConfigData* InputConfig = nullptr;

	// Pointer to the Input Mapping Context
	class UInputMappingContext* InputMapping = nullptr;

	
};
