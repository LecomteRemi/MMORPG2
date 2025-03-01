// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FightingCharacterAttributes.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API UFightingCharacterAttributes : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float walkSpeed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float interactionRange;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	float meleeRange;
	
};
