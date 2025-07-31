// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "CameraSettingsAsset.h"
#include "Projet_MMORPG_PlayerController.generated.h"
class ASkillAbility;
class AbilityList;
class AItem;
/**
 * 
 */
UCLASS()
class PROJET_MMORPG_API AProjet_MMORPG_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LeftClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TurnCameraLeftAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* TurnCameraRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TArray<class UInputAction*> actionBarActions;

	UPROPERTY(EditAnywhere)
	UCameraSettingsAsset * cameraSettings;


	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ASkillAbility>> skillBarList;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AItem>> itemBarList;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	void LeftClick();
	void TurnCameraLeft();
	void TurnCameraRight();
	void TargetClick(FHitResult & hit);
	void DisableTargeting();
	void UseAction(const FInputActionValue& value, int actionBarNumber);
	void UseItem(const FInputActionValue& value, int actionBarNumber);

	UFUNCTION(Client,Reliable)
	void SetActionBarInput();

	bool isTargetingForAbility;
	TSubclassOf<ASkillAbility> abilityUsed;

	
};
