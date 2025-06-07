// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
UENUM(BlueprintType)
enum class ETargetType : uint8 {
	NONE UMETA(DisplayName = "None"),
	LOCATION UMETA(DisplayName = "Location"),
	FIGHTER UMETA(DisplayName = "Fighter")
};