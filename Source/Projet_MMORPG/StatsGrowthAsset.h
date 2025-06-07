// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StatsGrowthAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API UStatsGrowthAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float expCoeff;


	UPROPERTY(EditAnywhere)
	float constitutionGrowth;
	UPROPERTY(EditAnywhere)
	float strengthGrowth;
	UPROPERTY(EditAnywhere)
	float defenseGrowth;
	UPROPERTY(EditAnywhere)
	float magicGrowth;
	UPROPERTY(EditAnywhere)
	float mindGrowth;
	UPROPERTY(EditAnywhere)
	float agilityGrowth;
	UPROPERTY(EditAnywhere)
	float skillGrowth;


};
