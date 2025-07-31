// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "ItemLoot.generated.h"

/**
 * 
 */
class AItem;

UCLASS()
class PROJET_MMORPG_API AItemLoot : public AInteractableActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AItem> itemClass;

	UPROPERTY(EditAnywhere)
	int quantity;
public:
	void virtual Interact(AFightingCharacter* interactor) override;
	UFUNCTION(Server, Reliable)
	void DestroyOnServer();
	UFUNCTION(Client, Reliable)
	void DestroyOnClient();

};
