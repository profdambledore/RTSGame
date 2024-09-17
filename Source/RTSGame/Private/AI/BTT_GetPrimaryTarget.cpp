// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT_GetPrimaryTarget.h"
#include "Unit/Unit_Controller.h"
#include "Unit/Unit_Parent.h"

EBTNodeResult::Type UBTT_GetPrimaryTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Clear TargetDead
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(TargetDead.SelectedKeyName, false);

	AUnit_Controller* Controller = Cast<AUnit_Controller>(OwnerComp.GetAIOwner());
	if (!Controller->TargetsInRange.IsEmpty()) {
		if (Controller->TargetsInRange[0]) {
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(OutTarget.SelectedKeyName, Controller->TargetsInRange[0]);
		}
		else {
			Controller->TargetsInRange.RemoveAt(0);
		}
	}
	return EBTNodeResult::Type();
}
