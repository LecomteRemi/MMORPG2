// Fill out your copyright notice in the Description page of Project Settings.


#include "StatBoostLoot.h"
#include "StatsComponent.h"

void AStatBoostLoot::Interact(AFightingCharacter* interactor) {

	interactor->GetStats()->IncreaseStats(statBoosted, quantity);
	Super::Interact(interactor);

}
