// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loot.h"
#include "StatBoostLoot.generated.h"

/**
 * 
 */
enum class StatEnum:uint8;
UCLASS()
class PROJET_MMORPG_API AStatBoostLoot : public ALoot
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	StatEnum statBoosted;

public:
	void virtual Interact(AFightingCharacter* interactor) override;
};
