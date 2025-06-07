// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAbilityState : uint8 {
	NONE UMETA(DisplayName = "None"),
	GET_IN_RANGE UMETA(DisplayName = "Get in range"),
	START_CASTING UMETA(DisplayName = "Start casting"),
	CAST UMETA(DisplayName = "Cast"),
	END_CASTING UMETA(DisplayName = "CastEnd casting")
};
