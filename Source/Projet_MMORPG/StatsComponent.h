// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsGrowthAsset.h"
#include "StatsComponent.generated.h"

UENUM(BlueprintType)
enum class StatEnum : uint8 {
	CONSTITUTION = 0 UMETA(DisplayName = "CONSTITUTION"),
	STRENGTH = 1  UMETA(DisplayName = "STRENGTH"),
	DEFENSE = 2     UMETA(DisplayName = "DEFENSE"),
	MAGIC = 3 UMETA(DisplayName = "MAGIC"),
	MIND = 4 UMETA(DisplayName = "MIND"),
	SKILL = 5 UMETA(DisplayName = "SKILL"),
	AGILITY = 6 UMETA(DisplayName = "AGILITY")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_MMORPG_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();
	UPROPERTY(EditAnywhere)
	UStatsGrowthAsset * statsGrowth;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnywhere)
	int level;

	UPROPERTY(EditAnywhere)
	float constitution;
	UPROPERTY(EditAnywhere)
	float strength;
	UPROPERTY(EditAnywhere)
	float defense;
	UPROPERTY(EditAnywhere)
	float magic;
	UPROPERTY(EditAnywhere)
	float mind;
	UPROPERTY(EditAnywhere)
	float skill;
	UPROPERTY(EditAnywhere)
	float agility;
	UPROPERTY(EditAnywhere)
	float attackSpeed;

public:	
	

	UFUNCTION(BlueprintCallable)
	int GetPVMax();
	UFUNCTION(BlueprintCallable)
	int GetManaMax();
	UFUNCTION(BlueprintCallable)
	float GetRegenPV();
	UFUNCTION(BlueprintCallable)
	float GetRegenMana();
	UFUNCTION(BlueprintCallable)
	int GetDamages();
	UFUNCTION(BlueprintCallable)
	int GetArmor();
	UFUNCTION(BlueprintCallable)
	int GetMagicDamages();
	UFUNCTION(BlueprintCallable)
	int GetArmureMagique();
	UFUNCTION(BlueprintCallable)
	float GetPrecision();
	UFUNCTION(BlueprintCallable)
	float GetAvoidance();
	UFUNCTION(BlueprintCallable)
	float GetParade();
	UFUNCTION(BlueprintCallable)
	float GetCritRate();
	UFUNCTION(BlueprintCallable)
	float GetAttackSpeed();

	UFUNCTION(BlueprintCallable)
	int GetLevel();

	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void LevelUp();
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	void IncreaseStats(StatEnum statEnum, int increment);
		
};
