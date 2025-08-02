// Fill out your copyright notice in the Description page of Project Settings.


#include "Projet_MMORPG_PlayerController.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "PlayerPawn.h"
#include "InteractableActor.h"
#include "SkillAbility.h"
#include "SkillAbilityDetails.h"
#include "AbilityList.h"

 void AProjet_MMORPG_PlayerController::BeginPlay() {
	 Super::BeginPlay();
	 this->bShowMouseCursor = true;
	 this->bEnableClickEvents = true;
	 this->bEnableMouseOverEvents = true;
	 if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	 {
		 Subsystem->AddMappingContext(DefaultMappingContext, 0);
	 }
	 FRotator defaultRotator(cameraSettings->defaultCameraPitch, 0, 0);
	 SetControlRotation(defaultRotator);

	 skillBarList.SetNum(10, true);
	// if (HasAuthority()) return;
	 /*if (Cast<APlayerPawn>(GetPawn())->abilityList != nullptr) {


		 
		 skillBarList[0] = Cast<APlayerPawn>(GetPawn())->abilityList->abilities[0]; //mockupAbilityClass;
		 
		 skillBarList[1] = Cast<APlayerPawn>(GetPawn())->abilityList->abilities[1];//Cast<APlayerPawn>(GetPawn())->abilityList->abilities[1];
		 skillBarList[2] = Cast<APlayerPawn>(GetPawn())->abilityList->abilities[2];//Cast<APlayerPawn>(GetPawn())->abilityList->abilities[2];

		 
	 }*/
	 SetActionBarInput();
	 
	 
	 
}
 void AProjet_MMORPG_PlayerController::SetActionBarInput_Implementation() {
	 if (Cast<APlayerPawn>(GetPawn())->abilityList != nullptr) {



		 skillBarList[0] = skillList[0]; //Cast<APlayerPawn>(GetPawn())->abilityList->abilities[0]; //mockupAbilityClass;

		 skillBarList[1] = skillList[1];//Cast<APlayerPawn>(GetPawn())->abilityList->abilities[1];//Cast<APlayerPawn>(GetPawn())->abilityList->abilities[1];
		 skillBarList[2] = skillList[2];//Cast<APlayerPawn>(GetPawn())->abilityList->abilities[2];//Cast<APlayerPawn>(GetPawn())->abilityList->abilities[2];
		 itemBarList.Add(GetPawn<APlayerPawn>()->healingItem);
		 itemBarList.Add(GetPawn<APlayerPawn>()->manaItem);


	 }
 }
 void AProjet_MMORPG_PlayerController::SetupInputComponent()
 {
	 Super::SetupInputComponent();
	 // Set up action bindings
	 if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	 {
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Triggered, this, &AProjet_MMORPG_PlayerController::LeftClick);
		EnhancedInputComponent->BindAction(TurnCameraLeftAction, ETriggerEvent::Triggered, this, &AProjet_MMORPG_PlayerController::TurnCameraLeft);
		EnhancedInputComponent->BindAction(TurnCameraRightAction, ETriggerEvent::Triggered, this, &AProjet_MMORPG_PlayerController::TurnCameraRight);

		skillBarList.SetNum(10, true);
		for (int i = 0; i < 3;i++) {
			EnhancedInputComponent->BindAction(actionBarActions[i], ETriggerEvent::Triggered, this, &AProjet_MMORPG_PlayerController::UseAction,i);
		}
		for (int i = 3; i < 5;i++) {
			EnhancedInputComponent->BindAction(actionBarActions[i], ETriggerEvent::Triggered, this, &AProjet_MMORPG_PlayerController::UseItem, i-3);
		}
	 }
 }

 void AProjet_MMORPG_PlayerController::LeftClick() {
	 FHitResult hit;
	 TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	 objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	 objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	 

	 if (GetHitResultUnderCursorForObjects(objectTypes,true,hit)){
		 if (isTargetingForAbility) {
			 TargetClick(hit);
		 } else if (hit.GetComponent()->GetCollisionObjectType() == ECC_WorldStatic) {
			 Cast<APlayerPawn>(GetPawn())->MoveToward(hit.ImpactPoint);
		 }
		 else if (hit.GetComponent()->GetCollisionObjectType() == ECC_Pawn) {
			 AFightingCharacter* otherFightingCharacter = Cast<AFightingCharacter>(hit.GetActor());
			 if (otherFightingCharacter) {
				 Cast<APlayerPawn>(GetPawn())->Attack(otherFightingCharacter);
			 }
			 else {
				 AInteractableActor* interactable = Cast<AInteractableActor>(hit.GetActor());
				 if (interactable && interactable->IsInteractable()) {
					 Cast<APlayerPawn>(GetPawn())->Interact(interactable);
				 }
			 }
		 }
	 }
 }

 void AProjet_MMORPG_PlayerController::TargetClick(FHitResult& hit) {

	 ETargetType targetType = abilityUsed->GetDefaultObject<ASkillAbility>()->skillAbilityDetails->targetType;
	 if (targetType == ETargetType::FIGHTER && hit.GetComponent()->GetCollisionObjectType() == ECC_Pawn) {
		 AFightingCharacter* otherFightingCharacter = Cast<AFightingCharacter>(hit.GetActor());
		 if (otherFightingCharacter) {
			 Cast<APlayerPawn>(GetPawn())->UseActionFighter(abilityUsed, otherFightingCharacter);
		 }

		 DisableTargeting();
	 }
	 else if (targetType == ETargetType::LOCATION && (hit.GetComponent()->GetCollisionObjectType() == ECC_WorldStatic)) {
		 Cast<APlayerPawn>(GetPawn())->UseActionLocation(abilityUsed, hit.ImpactPoint);

		 DisableTargeting();
	 }
 }

 void AProjet_MMORPG_PlayerController::TurnCameraLeft() {

	 AddYawInput(-GetWorld()->GetDeltaSeconds() * cameraSettings->cameraRotationSpeed);
 }
 void AProjet_MMORPG_PlayerController::TurnCameraRight() {

	 AddYawInput(GetWorld()->GetDeltaSeconds() * cameraSettings->cameraRotationSpeed);
 }


 void AProjet_MMORPG_PlayerController::UseItem(const FInputActionValue& value, int actionBarNumber) {

	 UE_LOG(LogTemp, Warning, TEXT("item numero %d"), actionBarNumber);
	 GetPawn<APlayerPawn>()->UseItem(itemBarList[actionBarNumber]);
 }
 void AProjet_MMORPG_PlayerController::UseAction(const FInputActionValue& value, int actionBarNumber) {
	 UE_LOG(LogTemp, Warning, TEXT("action numero %d"), actionBarNumber);

	 if (skillBarList[actionBarNumber] == nullptr) {

		 UE_LOG(LogTemp, Warning, TEXT("failure"), actionBarNumber);
		 return;
	 }
	 TSubclassOf<ASkillAbility> abilityToUse = skillBarList[actionBarNumber];
	 if (abilityToUse->GetDefaultObject<ASkillAbility>()->skillAbilityDetails->manaCost > Cast<APlayerPawn>(GetPawn())->fightingCharacter->mana) return;
	 if (abilityToUse->GetDefaultObject<ASkillAbility>()->skillAbilityDetails->targetType == ETargetType::NONE) {
		 Cast<APlayerPawn>(GetPawn())->UseAction(abilityToUse);

		 UE_LOG(LogTemp, Warning, TEXT("ko2"));
		 DisableTargeting();
	 }
	 else {
		 if (abilityUsed != abilityToUse) {
			 isTargetingForAbility = true;
			 abilityUsed = abilityToUse;

			 UE_LOG(LogTemp, Warning, TEXT("capacite choisie"));
		 }
		 else {
			 UE_LOG(LogTemp, Warning, TEXT("ko1"));
			 DisableTargeting();
		 }
	 }
 }
 void AProjet_MMORPG_PlayerController::DisableTargeting() {
	 isTargetingForAbility = false;
	 abilityUsed = nullptr;

	 UE_LOG(LogTemp, Warning, TEXT("capacite retiree"));
 }
