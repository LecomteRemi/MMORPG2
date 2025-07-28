// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ETargetType.h"
#include "SkillAbilityDetails.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API USkillAbilityDetails : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	ETargetType targetType;

	UPROPERTY(EditAnywhere)
	float range;

	UPROPERTY(EditAnywhere)
	float preparationTime;

	UPROPERTY(EditAnywhere)
	float delayTime;

	UPROPERTY(EditAnywhere)
	int manaCost;

	UPROPERTY(EditAnyWhere)
	float cooldown;
};
