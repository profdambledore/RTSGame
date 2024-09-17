// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetPrimaryTarget.generated.h"

UCLASS()
class RTSGAME_API UBTT_GetPrimaryTarget : public UBTTaskNode
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector OutTarget;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetDead;
	
};
