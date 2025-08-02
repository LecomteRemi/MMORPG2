// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelProgressionComponent.generated.h"

class UStatsComponent;
class UAbilityLevelUpList;
class AFightingCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_MMORPG_API ULevelProgressionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelProgressionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int currentExp;
	int neededExp;
	UPROPERTY(EditAnywhere)
	UAbilityLevelUpList* abilityList;
	int GetExpNeededForLevel(int level);

public:
	UPROPERTY(EditAnywhere)
	bool canGainExp;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(Server,Reliable)
	void AddExp(int gainedExp);
	bool CanGainExp();
	UStatsComponent* stats;
	AFightingCharacter* character;


		
};
