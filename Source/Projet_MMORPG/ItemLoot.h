// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Loot.h"
#include "ItemLoot.generated.h"

/**
 * 
 */
class AItem;

UCLASS()
class PROJET_MMORPG_API AItemLoot : public ALoot
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> itemClass;

public:
	void virtual Interact(AFightingCharacter* interactor) override;

};
