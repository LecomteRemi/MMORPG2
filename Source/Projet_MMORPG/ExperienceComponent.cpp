// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceComponent.h"
#include "StatsComponent.h"

// Sets default values for this component's properties
UExperienceComponent::UExperienceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExperienceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UExperienceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UExperienceComponent::AddExp(int expAdded) {
	bool leveledUp = false;
	currentExp += expAdded;
	while (currentExp >= GetNextLevelExpNeeded()) {
		currentExp -= GetNextLevelExpNeeded();
		stats->LevelUp();
		leveledUp = true;
	}
	return leveledUp;
}

int UExperienceComponent::GetNextLevelExpNeeded() {
	int currentLevel = stats->GetLevel();
	return (FMath::Square(currentLevel) - FMath::Square(currentLevel - 1) / 2) * 10;
}

void UExperienceComponent::SetStats(UStatsComponent* _stats) {
	this->stats = _stats;
}

