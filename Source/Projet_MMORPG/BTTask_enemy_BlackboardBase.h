// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_enemy_BlackboardBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API UBTTask_enemy_BlackboardBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_enemy_BlackboardBase();

private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription()const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="AI", meta=(AllowPrivateAccess = true))
	float AISearchRadius;

	void StartSearch();

	AAIController* AIController;

	const APawn* AIPawn;

	FVector PawnLocation;

	FNavLocation Location;
	
};
