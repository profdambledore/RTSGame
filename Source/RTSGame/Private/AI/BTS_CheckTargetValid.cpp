// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTS_CheckTargetValid.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Unit/Unit_Parent.h"
#include "Unit/Unit_Controller.h"

void UBTS_CheckTargetValid::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AUnit_Parent* TargetActor = Cast<AUnit_Parent>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(InPrimaryTarget.SelectedKeyName));
	if (TargetActor) {
		if (TargetActor->GetCurrentHealth() > 0) {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(OutValidility.SelectedKeyName, false);
		}
		else {
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(OutValidility.SelectedKeyName, true);
			AUnit_Controller* Controller = Cast<AUnit_Controller>(OwnerComp.GetAIOwner());
			Controller->TargetsInRange.Remove(TargetActor);
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(InPrimaryTarget.SelectedKeyName, nullptr);
		}
	}
}
