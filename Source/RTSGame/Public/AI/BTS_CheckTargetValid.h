// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_CheckTargetValid.generated.h"

UCLASS()
class RTSGAME_API UBTS_CheckTargetValid : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector InPrimaryTarget;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OutValidility;

};
