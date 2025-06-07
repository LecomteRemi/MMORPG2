// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

int UStatsComponent::GetPVMax() {
	return floor(constitution) * 5 + 10;
}
int UStatsComponent::GetManaMax() {
	return floor(mind) * 5 + 5;
}
float UStatsComponent::GetRegenPV() {
	return 0.02 * floor(constitution) + 0.01 * floor(mind) + 0.01;
}
float UStatsComponent::GetRegenMana() {
	return 0.1 * floor(mind) + 0.2 * floor(magic) + 1;
}
int UStatsComponent::GetDamages() {
	return floor(strength) + 2;
}
int UStatsComponent::GetArmor() {
	return floor(defense);
}
int UStatsComponent::GetMagicDamages() {
	return floor(magic) + 2;
}
int UStatsComponent::GetArmureMagique() {
	
	return floor(mind);
}
float UStatsComponent::GetPrecision() {
	return floor(skill) * 0.01 + 0.8;
}
float UStatsComponent::GetAvoidance() {
	return floor(agility) * 0.004 + 0.01;
}
float UStatsComponent::GetParade() {
	return 0.0008 * floor(skill) + 0.0005 * floor(defense);
}
float UStatsComponent::GetCritRate() {
	return 0.005 * floor(skill);
}
float UStatsComponent::GetAttackSpeed() {
	return attackSpeed;
}
int UStatsComponent::GetLevel() {
	return level;
}

void UStatsComponent::LevelUp() {
	level++;
	constitution += statsGrowth->constitutionGrowth;
	strength += statsGrowth->strengthGrowth;
	defense += statsGrowth->defenseGrowth;
	magic += statsGrowth->magicGrowth;
	mind += statsGrowth->mindGrowth;
	agility += statsGrowth->agilityGrowth;
	skill += statsGrowth->skillGrowth;
}

