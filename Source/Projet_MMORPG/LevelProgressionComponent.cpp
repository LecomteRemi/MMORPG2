// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelProgressionComponent.h"
#include "StatsComponent.h"
#include "AbilityLevelUpList.h"
#include "FightingCharacter.h"

// Sets default values for this component's properties
ULevelProgressionComponent::ULevelProgressionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULevelProgressionComponent::BeginPlay()
{
	Super::BeginPlay();
	if (abilityList != nullptr) {
		for (auto& elem : abilityList->abilities) {
			if (elem.Value == stats->GetLevel()) {
				character->AddAbility(elem.Key);
			}
		}
	}
	// ...
	
}


// Called every frame
void ULevelProgressionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULevelProgressionComponent::AddExp_Implementation(int gainedExp) {
	currentExp += gainedExp;
	while (currentExp >= neededExp) {
		stats->LevelUp();
		neededExp = GetExpNeededForLevel(stats->GetLevel());

		UE_LOG(LogTemp, Warning, TEXT("ability %d"), abilityList==nullptr);
		if (abilityList != nullptr) {

			for (auto& elem : abilityList->abilities) {

				UE_LOG(LogTemp, Warning, TEXT("ability %d %d"),elem.Value, stats->GetLevel());
				if (elem.Value == stats->GetLevel()) {
					character->AddAbility(elem.Key);

					UE_LOG(LogTemp, Warning, TEXT("ability ok"));
				}
			}
		}
	}
}

bool ULevelProgressionComponent::CanGainExp() {
	return canGainExp;
}
int ULevelProgressionComponent::GetExpNeededForLevel(int level) {
	return 10 * level;
}