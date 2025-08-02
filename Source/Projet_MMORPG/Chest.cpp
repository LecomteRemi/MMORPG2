// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Loot.h"
bool AChest::IsInteractable() {
	return !isOpen;
}
void AChest::Interact(AFightingCharacter* interactor) {
	OpenChest();
	for (auto& elem : loots) {
		
		float orientation = GetActorRotation().Yaw - FMath::DegreesToRadians(FMath::RandRange(-60, 60)) ; //FMath::RandRange(GetActorRotation().Yaw-60, GetActorRotation().Yaw+60);
		float range = FMath::RandRange(minLootRange, maxLootRange);
		float x = FMath::Cos(orientation) * range;
		float y = FMath::Sin(orientation)*range;
		ALoot* loot = GetWorld()->SpawnActor<ALoot>(elem.Key);
		loot->SetActorLocation(FVector(x, y, 0) + this->GetActorLocation());
		loot->SetQuantity(elem.Value);

	}
	//isOpen = true;
}
void AChest::OpenChest_Implementation() {
	isOpen = true;
}