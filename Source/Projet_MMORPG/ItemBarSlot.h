// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemBarSlot.generated.h"

/**
 * 
 */
class AProjet_MMORPG_PlayerController;
class APlayerPawn;
UCLASS()
class PROJET_MMORPG_API UItemBarSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	int nbItem;
	UPROPERTY(BlueprintReadOnly)
	UTexture2D* image;
private:
	int itembarSlotIdx;
	AProjet_MMORPG_PlayerController* controller;
	APlayerPawn* playerPawn;
public:
	UFUNCTION(BlueprintCallable)
	void SetSlotIdx(int idx);

	UFUNCTION(BlueprintCallable)
	void ActivateAction();

	UFUNCTION(BlueprintCallable)
	void UpdateActionSlotData();

	UFUNCTION(BlueprintCallable)
	void Init(int idx);
	
};
