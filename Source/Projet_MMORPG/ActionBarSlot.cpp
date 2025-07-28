// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBarSlot.h"
#include "Engine/Engine.h"
#include "Projet_MMORPG_PlayerController.h"
#include "PlayerPawn.h"
#include "SkillAbility.h"
#include "SkillAbilityDetails.h"
#include "ActionDetailsData.h"


void UActionBarSlot::SetSlotIdx(int idx) {
	this->actionBarSlotIdx = idx;
}
void UActionBarSlot::ActivateAction() {
	
}

void UActionBarSlot::UpdateActionSlotData() {
	TSubclassOf<ASkillAbility> ability = controller->actionBarList[actionBarSlotIdx];
	if (ability != nullptr && playerPawn->fightingCharacter != nullptr) {

		//UE_LOG(LogTemp, Warning, TEXT("Ok1"));
		if (playerPawn->fightingCharacter->abilityList.Contains(ability)) {

			UE_LOG(LogTemp, Warning, TEXT("Ok1 %d %d %d"), actionBarSlotIdx, IsRunningDedicatedServer(), playerPawn->fightingCharacter->abilityList.Contains(ability));
			actionCooldownPercentage = ability.GetDefaultObject()->skillAbilityDetails->cooldown == 0 ? 0 : playerPawn->fightingCharacter->abilityList[ability] / ability.GetDefaultObject()->skillAbilityDetails->cooldown;
			image = ability.GetDefaultObject()->actionDetails->image;
		}
		else {
			actionCooldownPercentage = 0;
			image = nullptr;
		}
	}
	//actionCooldownPercentage = playerPawn->fightingCharacter->abilityList[ability] / ability.GetDefaultObject()->skillAbilityDetails->cooldown;
}

void UActionBarSlot::Init(int idx) {
	controller = GetWorld()->GetFirstPlayerController<AProjet_MMORPG_PlayerController>();
	playerPawn = controller->GetPawn<APlayerPawn>();
	SetSlotIdx(idx);
}