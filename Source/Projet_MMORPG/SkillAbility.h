// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillAbility.generated.h"

/**
 * 
 */

class AFightingCharacter;
class USkillAbilityDetails;
class UActionDetailsData;
UCLASS(Abstract,Blueprintable)
class PROJET_MMORPG_API ASkillAbility : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void ActivateAbility(AFightingCharacter * caster);

	UPROPERTY(EditAnywhere)
	USkillAbilityDetails* skillAbilityDetails;
	UPROPERTY(EditAnywhere)
	UActionDetailsData* actionDetails;



};
