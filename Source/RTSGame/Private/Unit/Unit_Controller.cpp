// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/Unit_Controller.h"

#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionSystem.h"

#include "Unit/Unit_Parent.h"

AUnit_Controller::AUnit_Controller()
{
	// Find and store the Behaviour Tree
	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/AI/BT_UnitBehaviorTree"));
	if (BTObject.Succeeded()) { BT = BTObject.Object; }

	// Create the components for the AI
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	// Next the AI Components and the sight config
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Unit Perception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	// Register the sight config for the AI Perception Component
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	AIPerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AUnit_Controller::SightSenseUnit);
}

void AUnit_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AUnit_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	Unit = Cast<AUnit_Parent>(InPawn);

	// Also register this unit as a sight stimuli source
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), Unit);

	// Setup the Sight Config
	SightConfig->SightRadius = 12000.0f;
	SightConfig->LoseSightRadius = (12000.0f + 20.0f);
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AIPerceptionComponent->ConfigureSense(*SightConfig);

	// Check if the InPawn is valid and that the BT has been set
	if (InPawn && BT) {
		// Initialize the BlackboardComponent with BT's BlackboardAsset
		BBC->InitializeBlackboard(*BT->BlackboardAsset);

		// Set the SelfActor in the Blackboard
		BBC->SetValueAsObject(FName("SelfActor"), InPawn);
		BBC->SetValueAsFloat(FName("InRange"), 500.0f);

		//UpdateAIActive(true);
	}
}

void AUnit_Controller::UpdateAIActive(bool bActivateAI)
{
	if (bActivateAI) {
		BTC->StartTree(*BT);
	}
	else {
		BTC->StopTree();
	}
}

void AUnit_Controller::UpdateBlackboardValues(int Damage, int Range, float Cooldown)
{
	if (BBC) {
		BBC->SetValueAsInt(FName("AttackDamage"), Damage);
		BBC->SetValueAsInt(FName("AttackRange"), Range);
		BBC->SetValueAsFloat(FName("Cooldown"), Cooldown);
	}
}

void AUnit_Controller::SightSenseUnit(const TArray<AActor*>& DetectedPawn)
{
	for (AActor* i : DetectedPawn) {
		AUnit_Parent* tar = Cast<AUnit_Parent>(i);
		if (tar->GetTeam() != Unit->GetTeam()){
			if (TargetsInRange.Contains(i)) {
				TargetsInRange.Remove(i);
			}
			else {
				TargetsInRange.Add(i);
			}
		}
	}
}
