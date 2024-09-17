// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SimulationController.h"

#include "Unit/Unit_Parent.h"
#include "UI/PlayerWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASimulationController::ASimulationController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASimulationController::BeginPlay()
{
	Super::BeginPlay();

	// Create the material instances for each team
	CreateMaterialInstances();

	// Get all of the units in the world and sort them into their two teams
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUnit_Parent::StaticClass(), FoundActors);
	for (AActor* i : FoundActors) {
		if (i->ActorHasTag("Red")) {
			TeamOneUnits.Add(Cast<AUnit_Parent>(i));
		}
		if (i->ActorHasTag("Blue")) {
			TeamTwoUnits.Add(Cast<AUnit_Parent>(i));
		}
	}

	for (AUnit_Parent* i : TeamTwoUnits) {
		i->SetTeam(2, TeamTwoMaterial);
	}

	// Colour each team
	for (AUnit_Parent* i : TeamOneUnits) {
		i->SetTeam(1, TeamOneMaterial);
	}
}

// Called every frame
void ASimulationController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASimulationController::StartSimulation(UPlayerWidget* NewPlayerUI)
{
	PlayerUI = NewPlayerUI;

	// Start every unit in each team
	for (AUnit_Parent* i : TeamTwoUnits) {
		i->StartUnit();
	}

	for (AUnit_Parent* i : TeamOneUnits) {
		i->StartUnit();
	}

}

void ASimulationController::RemoveUnitFromTeam(int InTeam, AUnit_Parent* UnitToRemove)
{
	if (InTeam == 1) {
		// Remove the unit from the team one array
		TeamOneUnits.Remove(UnitToRemove);
		if (TeamOneUnits.IsEmpty()) {
			PlayerUI->ShowWinner(false);
		}
	}
	else if (InTeam == 2) {
		TeamTwoUnits.Remove(UnitToRemove);
		if (TeamTwoUnits.IsEmpty()) {
			PlayerUI->ShowWinner(true);
		}
	}
}

