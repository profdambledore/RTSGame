// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_UpdateDistanceToTarget.generated.h"


UCLASS()
class RTSGAME_API UBTS_UpdateDistanceToTarget : public UBTService
{
	GENERATED_BODY()

	UBTS_UpdateDistanceToTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Unit;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Target;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Range;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OutInRange;

};
