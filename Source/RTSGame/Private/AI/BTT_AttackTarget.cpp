// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTT_AttackTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Unit/Unit_Parent.h"
#include "Unit/Unit_Controller.h"

EBTNodeResult::Type UBTT_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AUnit_Parent* Unit = Cast<AUnit_Parent>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	if (Unit) {
		if (Unit->ModifyHealth(OwnerComp.GetBlackboardComponent()->GetValueAsInt(Damage.SelectedKeyName))) {
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
	}
	

	return EBTNodeResult::Type();
}
