// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class AFightingCharacter;
class UActionDetailsData;
UCLASS(Abstract, Blueprintable)
class PROJET_MMORPG_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	



	UPROPERTY(EditAnywhere)
	UActionDetailsData* actionDetails;

	UFUNCTION(BlueprintNativeEvent)
	void ActivateItem(AFightingCharacter* user);

};
