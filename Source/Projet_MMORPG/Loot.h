// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Loot.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API ALoot : public AInteractableActor
{
	GENERATED_BODY()
public:
	void virtual Interact(AFightingCharacter* interactor) override;
	void SetQuantity(int quantity_);
protected:

	UPROPERTY(EditAnywhere)
	int quantity;
	UFUNCTION(Server, Reliable)
	void DestroyOnServer();
	UFUNCTION(Client, Reliable)
	void DestroyOnClient();
};
