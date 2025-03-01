// Fill out your copyright notice in the Description page of Project Settings.


#include "Projet_MMORPG_PlayerController.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "PlayerPawn.h"

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
	 FRotator defaultRotator(defaultCameraPitch, 0, 0);
	 SetControlRotation(defaultRotator);
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
	 }
 }

 void AProjet_MMORPG_PlayerController::LeftClick() {

	 UE_LOG(LogTemp, Warning, TEXT("click"));
	 FHitResult hit;
	 TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	 objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	 objectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	 

	 if (GetHitResultUnderCursorForObjects(objectTypes,true,hit)){
		 if (hit.GetComponent()->GetCollisionObjectType() == ECC_WorldStatic) {
			 UE_LOG(LogTemp, Warning, TEXT("static"));
			 Cast<APlayerPawn>(GetPawn())->MoveToward(hit.ImpactPoint);
		 }
		 else if (hit.GetComponent()->GetCollisionObjectType() == ECC_Pawn) {
			 UE_LOG(LogTemp, Warning, TEXT("pawn"));
			 AFightingCharacter* otherFightingCharacter = Cast<AFightingCharacter>(hit.GetActor());
			 if (otherFightingCharacter) {
				 Cast<APlayerPawn>(GetPawn())->Attack(otherFightingCharacter);
			 }
		 }
	 }
 }

 void AProjet_MMORPG_PlayerController::TurnCameraLeft() {

	 AddYawInput(-GetWorld()->GetDeltaSeconds() * cameraRotationSpeed);
 }
 void AProjet_MMORPG_PlayerController::TurnCameraRight() {

	 AddYawInput(GetWorld()->GetDeltaSeconds() * cameraRotationSpeed);
 }
