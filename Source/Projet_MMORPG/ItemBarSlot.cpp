// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBarSlot.h"

#include "Projet_MMORPG_PlayerController.h"
#include "PlayerPawn.h"
#include "ActionDetailsData.h"
#include "Item.h"


void UItemBarSlot::SetSlotIdx(int idx) {
	this->itembarSlotIdx = idx;
}
void UItemBarSlot::ActivateAction() {

}

void UItemBarSlot::UpdateActionSlotData() {
	TSubclassOf<AItem> item = controller->itemBarList[itembarSlotIdx];
	if (item != nullptr && playerPawn->fightingCharacter != nullptr) {

		//UE_LOG(LogTemp, Warning, TEXT("Ok1"));
		if (playerPawn->fightingCharacter->itemList.Contains(item)) {

			nbItem = playerPawn->fightingCharacter->GetNbItem(item);
			image = item.GetDefaultObject()->actionDetails->image;

		}
		else {

			nbItem = 0;
			image = nullptr;
		}
	}
}

void UItemBarSlot::Init(int idx) {
	controller = GetWorld()->GetFirstPlayerController<AProjet_MMORPG_PlayerController>();
	playerPawn = controller->GetPawn<APlayerPawn>();
	SetSlotIdx(idx);
}