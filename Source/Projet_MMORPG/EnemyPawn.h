// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "FightingCharacter.h"
#include "FightingCharacterAttributes.h"

#include "EnemyPawn.generated.h"

class AInteractableActor;
class UAbilityList;

UCLASS()
class PROJET_MMORPG_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

private:
	bool initiated;
public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFightingCharacter> fightingCharacterClass;

	UPROPERTY(BlueprintReadOnly, Replicated)
	AFightingCharacter* fightingCharacter;


	UPROPERTY(EditAnywhere)
	UFightingCharacterAttributes* attributes;

	UPROPERTY(EditAnywhere)
	UAbilityList* abilityList;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void MoveToward(FVector location);

	UFUNCTION(Server, Reliable)
	void Attack(AFightingCharacter* otherFightingCharacter);

	UFUNCTION(Server, Reliable)
	void Interact(AInteractableActor* interactable);

	UFUNCTION(Server, Reliable)
	void StopAction();

	UFUNCTION()
	void Init();

	UFUNCTION(Server, Reliable)
	void UseAction(TSubclassOf<ASkillAbility> skillAbilityClass);

	UFUNCTION(Server, Reliable)
	void UseActionFighter(TSubclassOf<ASkillAbility> skillAbilityClass, AFightingCharacter* target);

	UFUNCTION(Server, Reliable)
	void UseActionLocation(TSubclassOf<ASkillAbility> skillAbilityClass, const FVector& target);

	UFUNCTION()
	void AddAbility(TSubclassOf<ASkillAbility> ability);


};