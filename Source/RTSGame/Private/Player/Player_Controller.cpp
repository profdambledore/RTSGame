// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Player_Controller.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Input/Input_ConfigData.h"
#include "Player/Player_Character.h"

APlayer_Controller::APlayer_Controller()
{
	// Find the input objects
	// First, find the Input Context Data
	ConstructorHelpers::FObjectFinder<UInput_ConfigData>ICDObject(TEXT("/Game/Input/ICD_RTSGame"));
	if (ICDObject.Succeeded()) { InputConfig = ICDObject.Object; }

	// Last, find the Input Mapping Context
	ConstructorHelpers::FObjectFinder<UInputMappingContext>IMCObject(TEXT("/Game/Input/IMC_RTSGame"));
	if (IMCObject.Succeeded()) { InputMapping = IMCObject.Object; }
}

void APlayer_Controller::BeginPlay()
{
	// Called when the game starts or when spawned
	Super::BeginPlay();
}

void APlayer_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if the input object pointers are valid
	if (InputConfig && InputMapping) {
		// Get and store the local player subsystem
		auto EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

		// Then clear any existing mapping, then add the new mapping
		EnhancedInputSubsystem->ClearAllMappings();
		EnhancedInputSubsystem->AddMappingContext(InputMapping, 0);

		// Get the EnhancedInputComponent
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

		// Bind the inputs
		EnhancedInputComponent->BindAction(InputConfig->MoveXInput, ETriggerEvent::Triggered, this, &APlayer_Controller::MoveX);
		EnhancedInputComponent->BindAction(InputConfig->MoveYInput, ETriggerEvent::Triggered, this, &APlayer_Controller::MoveY);
		EnhancedInputComponent->BindAction(InputConfig->RotateCamera, ETriggerEvent::Triggered, this, &APlayer_Controller::RotateCamera);
		EnhancedInputComponent->BindAction(InputConfig->ZoomCamera, ETriggerEvent::Triggered, this, &APlayer_Controller::ZoomCamera);
	}
}

void APlayer_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Cast to the character pawn and store it
	Character = Cast<APlayer_Character>(GetPawn());
}

void APlayer_Controller::MoveX(const FInputActionValue& Value)
{
	// Check if the Character Pointer has been created successfully.  If so...
	if (Character) {
		// Call the MoveX command on the character
		Character->MoveX(Value.Get<float>());
	}
}

void APlayer_Controller::MoveY(const FInputActionValue& Value)
{
	// Check if the Character Pointer has been created successfully.  If so...
	if (Character) {
		// Call the MoveY command on the character
		Character->MoveY(Value.Get<float>());
	}
}

void APlayer_Controller::RotateCamera(const FInputActionValue& Value)
{
	// Check if the Character Pointer has been created successfully.  If so...
	if (Character) {
		Character->RotateCameraByStep(GetInputValueIsPositive(Value.Get<float>()));
	}
}

void APlayer_Controller::ZoomCamera(const FInputActionValue& Value)
{
	// Check if the Character Pointer has been created successfully.  If so...
	if (Character) {
		Character->ZoomCameraByStep(GetInputValueIsPositive(Value.Get<float>()));
	}
}

/// -- Utility Functions --
// Called to return if an input value is positive or negative
bool APlayer_Controller::GetInputValueIsPositive(float InInputValue)
{
	if (InInputValue == 1) {
		return false;
	}
	return true;
}