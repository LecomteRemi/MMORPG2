// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_enemy_BlackboardBase.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_enemy_BlackboardBase::UBTTask_enemy_BlackboardBase()
{
	NodeName = TEXT("AI Patrol");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_enemy_BlackboardBase, BlackboardKey));

}

EBTNodeResult::Type UBTTask_enemy_BlackboardBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	StartSearch();

	AIController = OwnerComp.GetAIOwner();
	AIPawn = AIController->GetPawn();

	PawnLocation = AIPawn->GetActorLocation();

	const UNavigationSystemV1* Navigation = UNavigationSystemV1::GetCurrent(GetWorld());
	if (IsValid(Navigation) && Navigation->GetRandomPointInNavigableRadius(PawnLocation, AISearchRadius, Location))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_enemy_BlackboardBase::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector:"), *BlackboardKey.SelectedKeyName.ToString());
}

void UBTTask_enemy_BlackboardBase::StartSearch()
{
	AISearchRadius = 700;
}