// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTS_UpdateDistanceToTarget.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTS_UpdateDistanceToTarget::UBTS_UpdateDistanceToTarget()
{
	NodeName = "Update Distance To Target";
}

void UBTS_UpdateDistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* UnitActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Unit.SelectedKeyName));
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	float AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsInt(Range.SelectedKeyName);

	// If both are set and valid, then calculate distance between the two
	if (UnitActor && TargetActor) {
		float DistanceBetween = FVector::Dist(UnitActor->GetActorLocation(), TargetActor->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat(OutInRange.SelectedKeyName, DistanceBetween - AttackRange);
	}

}
