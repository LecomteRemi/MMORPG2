// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExperienceComponent.generated.h"

class UStatsComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_MMORPG_API UExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExperienceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStatsComponent* stats;

	UPROPERTY(EditAnywhere)
	int currentExp;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool AddExp(int expAdded);
	int GetNextLevelExpNeeded();

	void SetStats(UStatsComponent* _stats);



		
};
