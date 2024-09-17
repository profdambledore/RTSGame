// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Player_Character.generated.h"

class APlayer_Controller;

UCLASS()
class RTSGAME_API APlayer_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// -- Inputs --
	// Called to make the player move on the X axis (forward/backward)
	void MoveX(float AxisValue);

	// Called to make the player move on the Y axis (strafe left/right)
	void MoveY(float AxisValue);

	// Called to rotate the camera by CameraRotationStep in a direction.  True if rotation is clockwise.
	void RotateCameraByStep(bool bRotateClockwise);

	// Called to modify the camera's zoom by a set amount (ZoomStep)
	void ZoomCameraByStep(bool bZoomOut);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

protected:
	/// -- Components --
	// Camera Spring Arm
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* CameraSpringArm = nullptr;

	// Camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera = nullptr;

private:
	/// -- Pointers --
	// Pointer to the controller of this player
	APlayer_Controller* PC = nullptr;

	// Pointer to the UI added to the viewport
	class UPlayerWidget* UI = nullptr;

	/// -- Camera Properties --
	// Float to denote zoom step value
	int ZoomStep = 100;

	// Ints denoting the max and min zoom of the camera
	int ZoomMin = 300;
	int ZoomMax = 4000;

	// Float to denote rotation step value
	float RotationStep = 1;

	// Int denoting the current rotation step multiplier
	// Incremented when rotating clockwise, or decremented when counterclockwise
	int CurrentStep = 0;
};
