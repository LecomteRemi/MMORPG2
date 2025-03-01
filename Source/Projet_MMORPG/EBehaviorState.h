// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBehaviorState : uint8 {
	NONE UMETA(DisplayName="None"),
	MOVE UMETA(DisplayName = "Move"),
	ATTACK UMETA(DisplayName = "Attack"),
	INTERACT UMETA(DisplayName = "Interact"),
	CAST UMETA(DisplayName = "Cast")
};
