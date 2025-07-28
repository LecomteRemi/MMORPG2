// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ActionDetailsData.generated.h"

UCLASS()
class PROJET_MMORPG_API UActionDetailsData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString name;

	UPROPERTY(EditAnywhere)
	FString description;

	UPROPERTY(EditAnywhere)
	UTexture2D* image;
	
};
