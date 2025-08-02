// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityLevelUpList.generated.h"

/**
 * 
 */
class ASkillAbility;
UCLASS()
class PROJET_MMORPG_API UAbilityLevelUpList : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<ASkillAbility>, int> abilities;
};
