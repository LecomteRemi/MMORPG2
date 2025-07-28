// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionBarSlot.generated.h"

/**
 * 
 */

class AProjet_MMORPG_PlayerController;
class APlayerPawn;
UCLASS()
class PROJET_MMORPG_API UActionBarSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly)
	float actionCooldownPercentage;
	UPROPERTY(BlueprintReadOnly)
	UTexture2D* image;
private:
	int actionBarSlotIdx;
	AProjet_MMORPG_PlayerController * controller;
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
