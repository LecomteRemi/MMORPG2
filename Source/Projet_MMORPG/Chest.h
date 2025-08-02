// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Chest.generated.h"

class ALoot;

/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API AChest : public AInteractableActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<ALoot>, int> loots;
	bool isOpen = false;
	UPROPERTY(EditAnywhere)
	float minLootRange;
	UPROPERTY(EditAnywhere)
	float maxLootRange;
public:

	virtual bool IsInteractable() override;
	virtual void Interact(AFightingCharacter* interactor) override;
	UFUNCTION(NetMulticast, Reliable)
	void OpenChest();
	
};
