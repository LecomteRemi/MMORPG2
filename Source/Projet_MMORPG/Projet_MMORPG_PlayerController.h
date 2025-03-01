// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "Projet_MMORPG_PlayerController.generated.h"

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

	UPROPERTY(EditAnywhere)
	float cameraRotationSpeed=10;
	UPROPERTY(EditAnywhere)
	float defaultCameraPitch;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	void LeftClick();
	void TurnCameraLeft();
	void TurnCameraRight();

	
};
