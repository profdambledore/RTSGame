// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulationController.generated.h"

UCLASS()
class RTSGAME_API ASimulationController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulationController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to start the simulation
	void StartSimulation(class UPlayerWidget* NewPlayerUI);

	// Called when a unit dies to remove the pointer from the team array
	void RemoveUnitFromTeam(int InTeam, class AUnit_Parent* UnitToRemove);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to create two material instances for each team
	UFUNCTION(BlueprintImplementableEvent)
	void CreateMaterialInstances();

public:	

protected:
	/// -- Material Instances --
	// Material Instance for team one
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
	UMaterial* TeamOneMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
	UMaterial* TeamTwoMaterial = nullptr;

	/// -- Team Colours --
	// Colour for team one
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
	FLinearColor TeamOneColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
	FLinearColor TeamTwoColour;

	/// -- Team Arrays --
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
	TArray< AUnit_Parent*> TeamOneUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teams")
	TArray< AUnit_Parent*> TeamTwoUnits;

private:
	class UPlayerWidget* PlayerUI = nullptr;
};
