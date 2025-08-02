// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLoot.h"

void AItemLoot::Interact(AFightingCharacter* interactor) {

	interactor->IncreaseNbItem(itemClass, quantity);
	Super::Interact(interactor);

}

