// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilityList.generated.h"

class ASkillAbility;
/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API UAbilityList : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ASkillAbility>> abilities;
};
