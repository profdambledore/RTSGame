// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/Unit_Parent.h"

#include "Unit/Unit_Controller.h"
#include "Kismet/GameplayStatics.h"

#include "Game/SimulationController.h"

// Sets default values
AUnit_Parent::AUnit_Parent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add the static mesh component
	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display Mesh"));
	DisplayMesh->SetupAttachment(GetMesh(), "");
	DisplayMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));

	AIStimuliComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Unit Stimuli Component"));
}

// Called when the game starts or when spawned
void AUnit_Parent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	// Cast to and store a pointer to the controller
	Controller = Cast<AUnit_Controller>(GetController());

	// Update the Blackboard of the Behaviour Tree with the damage, range and cooldown values
	if (Controller) {
		Controller->UpdateBlackboardValues(AttackDamage, AttackRange, AttackCooldown);
	}
}

// Called every frame
void AUnit_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnit_Parent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnit_Parent::SetTeam(int NewTeam, UMaterial* NewMatInstance)
{
	TeamID = NewTeam;

	DisplayMesh->SetMaterial(0, NewMatInstance);
}

bool AUnit_Parent::ModifyHealth(int Amount)
{
	if (CurrentHealth > 0) {
		// Remove Damage from CurrentHealth
		CurrentHealth += Amount;

		// If the unit's current health now exceeds MaxHealth, set CurrentHealth to MaxHealth
		if (CurrentHealth >= MaxHealth) CurrentHealth = MaxHealth;
		// If the unit has run out of health, stop it's AI and call it's death animation
		if (CurrentHealth <= 0) {
			Controller->UpdateAIActive(false);
			Cast< ASimulationController>(UGameplayStatics::GetActorOfClass(GetWorld(), ASimulationController::StaticClass()))->RemoveUnitFromTeam(TeamID, this);
			PlayDeathAnimation();
			return true;
		}
	}
	
	return false;
}

void AUnit_Parent::StartUnit()
{
	Controller->UpdateAIActive(true);
}

