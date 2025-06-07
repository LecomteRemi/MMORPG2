// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CameraSettingsAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API UCameraSettingsAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float cameraRotationSpeed = 10;
	UPROPERTY(EditAnywhere)
	float defaultCameraPitch;

	
};
