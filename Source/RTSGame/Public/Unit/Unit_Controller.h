// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "Unit_Controller.generated.h"

UCLASS()
class RTSGAME_API AUnit_Controller : public AAIController
{
	GENERATED_BODY()

public:
	// Constructor
	AUnit_Controller();

	// Called when the AI Possesses a character
	virtual void OnPossess(APawn* InPawn) override;

	// Called to play or stop the AI from controlling the character
	void UpdateAIActive(bool bActivateAI);

	// Called to update the default blackboard values
	void UpdateBlackboardValues(int Damage, int Range, float Cooldown);

	// Called to get the unit controlled
	class AUnit_Parent* GetUnit() { return Unit; };

	// Called to get the targets in range array
	TArray<AActor*> GetTargetsInRange() { return TargetsInRange; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the AI senses a new stimuli
	UFUNCTION()
	void SightSenseUnit(const TArray<AActor*>& DetectedPawn);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> TargetsInRange;

protected:
	/// -- AI Assets --
	// Behaviour Tree for the Person
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Assets")
	UBehaviorTree* BT = nullptr;

	// Behavior Tree Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Components")
	UBehaviorTreeComponent* BTC = nullptr;

	// Blackboard Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Components")
	UBlackboardComponent* BBC = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionComponent* AIPerceptionComponent = nullptr;

	// Config for the AISense_Sight
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAISenseConfig_Sight* SightConfig = nullptr;

private:
	// Pointer to possessed unit
	class AUnit_Parent* Unit = nullptr;
};
