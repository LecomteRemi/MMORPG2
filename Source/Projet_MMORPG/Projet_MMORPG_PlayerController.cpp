// Fill out your copyright notice in the Description page of Project Settings.


#include "Projet_MMORPG_PlayerController.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "PlayerPawn.h"
#include "InteractableActor.h"
#include "SkillAbility.h"
#include "SkillAbilityDetails.h"

 void AProjet_MMORPG_PlayerController::BeginPlay() {
	 Super::BeginPlay();
	 this->bShowMouseCursor = true;
	 this->bEnableClickEvents = true;
	 this->bEnableMouseOverEvents = true;
	 UE_LOG(LogTemp, Warning, TEXT("ok"));
	 if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	 {
		 Subsystem->AddMappingContext(DefaultMappingContext, 0);
	 }
	 FRotator defaultRotator(cameraSettings->defaultCameraPitch, 0, 0);
	 SetControlRotation(defaultRotator);

	 actionBarList.SetNum(10, true);
	 actionBarList[0] = mockupAbilityClass;
	 actionBarList[1] = mockupAbilityClassLocation;
	 actionBarList[2] = mockupAbilityClassFighter;
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
		for (int i = 0; i < actionBarActions.Num();i++) {
			EnhancedInputComponent->BindAction(actionBarActions[i], ETriggerEvent::Triggered, this, &AProjet_MMORPG_PlayerController::UseAction,i);
		}
	 }
 }

 void AProjet_MMORPG_PlayerController::LeftClick() {

	 UE_LOG(LogTemp, Warning, TEXT("click"));
	 FHitResult hit;
	 TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	 objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	 objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	 

	 if (GetHitResultUnderCursorForObjects(objectTypes,true,hit)){
		 if (isTargetingForAbility) {
			 TargetClick(hit);
		 } else if (hit.GetComponent()->GetCollisionObjectType() == ECC_WorldStatic) {
			 UE_LOG(LogTemp, Warning, TEXT("static"));
			 Cast<APlayerPawn>(GetPawn())->MoveToward(hit.ImpactPoint);
		 }
		 else if (hit.GetComponent()->GetCollisionObjectType() == ECC_Pawn) {
			 UE_LOG(LogTemp, Warning, TEXT("pawn"));
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
	 UE_LOG(LogTemp, Warning, TEXT("targetClick"));
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

 void AProjet_MMORPG_PlayerController::UseAction(const FInputActionValue& value, int actionBarNumber) {
	 UE_LOG(LogTemp, Warning, TEXT("action numero %d"), actionBarNumber);

	 if (actionBarList[actionBarNumber] == nullptr) return;
	 TSubclassOf<ASkillAbility> abilityToUse = actionBarList[actionBarNumber];
	 if (abilityToUse->GetDefaultObject<ASkillAbility>()->skillAbilityDetails->manaCost > Cast<APlayerPawn>(GetPawn())->fightingCharacter->mana) return;
	 if (abilityToUse->GetDefaultObject<ASkillAbility>()->skillAbilityDetails->targetType == ETargetType::NONE) {
		 Cast<APlayerPawn>(GetPawn())->UseAction(abilityToUse);
		 DisableTargeting();
	 }
	 else {
		 if (abilityUsed != abilityToUse) {
			 isTargetingForAbility = true;
			 abilityUsed = abilityToUse;

			 UE_LOG(LogTemp, Warning, TEXT("capacite choisie"));
		 }
		 else {
			 DisableTargeting();
		 }
	 }
 }
 void AProjet_MMORPG_PlayerController::DisableTargeting() {
	 isTargetingForAbility = false;
	 abilityUsed = nullptr;

	 UE_LOG(LogTemp, Warning, TEXT("capacite retiree"));
 }
