// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/StaticMeshComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "Unit_Parent.generated.h"

UCLASS()
class RTSGAME_API AUnit_Parent : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit_Parent();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called by a unit to get the team of the unit
	int GetTeam() { return TeamID; }

	// Called to set the team of the unit
	void SetTeam(int NewTeam, UMaterial* NewMatInstance);

	// Called to get the health value of the unit
	int GetCurrentHealth() { return CurrentHealth; }

	// Called by a unit to modify this unit's health
	// Returns true if the unit was killed, false if not
	bool ModifyHealth(int Amount);

	// Called to start this unit
	void StartUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the unit dies to play a small death animation
	// Could set up in C++ as it uses a timeline, but this is purely visual
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathAnimation();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit Stats")
	int CurrentHealth;

protected:
	/// -- Components --
	// StaticMeshComponent displaying the unit's mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* DisplayMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionStimuliSourceComponent* AIStimuliComponent = nullptr;

	/// -- Unit Properties --
	// int denoting the unit's team (-1 if unset)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Stats")
	int TeamID = -1;

	// ints denoting the unit's max and current health values
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Stats")
	int MaxHealth;


	/// -- Attacking Properties --
	// Int denoting the attack damage of the unit
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Stats")
	int AttackDamage;

	// Float denoting the cooldown between this unit's attacks
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Stats")
	float AttackCooldown;

	// Int denoting the unit's attack range (in uu)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Unit Stats")
	int AttackRange;

private:
	// Pointer to the AI Controller of this unit
	class AUnit_Controller* Controller = nullptr;
};
