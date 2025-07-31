// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EBehaviorState.h"
#include "EAbilityState.h"
#include "ETargetType.h"
#include "FightingCharacterAttributes.h"
#include "FightingCharacter.generated.h"

union SpellTarget {
	AFightingCharacter* fightingCharacter;
	FVector location;

};


class AInteractableActor;
class UStatsComponent;

class UAbilityList;
class ASkillAbility;
class AItem;

UCLASS(BlueprintType)
class PROJET_MMORPG_API AFightingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFightingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	EBehaviorState currentState;

	UPROPERTY(EditAnywhere)
	EAbilityState currentAbilityState;

	ETargetType spellTargetType;



	UPROPERTY()
	FVector targetLocation;

	UPROPERTY()
	AFightingCharacter* targetEnemy;

	UPROPERTY()
	AFightingCharacter* targetSpellFighter;

	UPROPERTY()
	AInteractableActor* targetInteraction;

	SpellTarget spellTarget;
	UPROPERTY(EditAnywhere)
	UFightingCharacterAttributes* attributes;

	TSubclassOf<ASkillAbility> usedAbilityClass;
	ASkillAbility * usedAbility;


	UFUNCTION()
	void MoveToward(const FVector& location);
	void Attack(AFightingCharacter * enemy);

	void RegenPVAndMana();

	void UpdateCooldown();

	double lastAttackTime;

	double startCastingTime;
	double endCastingTime;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStatsComponent* stats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	float PV;

	

	virtual void  Die();
	//targetInteractableObject

public:	

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated)
	float mana;

	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<ASkillAbility>, float> abilityList;
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<AItem>, int> itemList;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpawnAIController();

	void MoveCommand(const FVector & location);

	void AttackCommand(AFightingCharacter* enemy);
	void InteractCommand(AInteractableActor * interactable);
	void StopCommand();
	void CastCommand(TSubclassOf<ASkillAbility> abilityClass,AFightingCharacter* target);
	void CastCommand(TSubclassOf<ASkillAbility> abilityClass, FVector target);
	void CastCommand(TSubclassOf<ASkillAbility> abilityClass);
	void UseItem(TSubclassOf<AItem> itemClass);
	void Update();
	void UpdateAbility();
	void SetAttributes(UFightingCharacterAttributes* attributes);
	void TakeHit(int damage);

	UStatsComponent * GetStats();

	UFUNCTION()
	virtual void SignalDeathOf(AFightingCharacter* deadFighter);

	UFUNCTION(BlueprintCallable)
	void EndCasting();

	bool CanInterruptAction();

	UFUNCTION()
	void AddAbility(TSubclassOf<ASkillAbility> ability);

	UFUNCTION(NetMulticast, Reliable)
	void SetCooldownOnClient(TSubclassOf<ASkillAbility> ability);


	UFUNCTION()
	int GetNbItem(TSubclassOf<AItem> item);
	UFUNCTION(NetMulticast, Reliable)
	void IncreaseNbItem(TSubclassOf<AItem> item, int increment);
	UFUNCTION(NetMulticast, Reliable)
	void DecreaseNbItem(TSubclassOf<AItem> item, int decrement);

	UFUNCTION(BlueprintCallable)
	void IncreasePV(int increment);
	UFUNCTION(BlueprintCallable)
	void DecreasePV(int decrement);
	UFUNCTION(BlueprintCallable)
	void IncreaseMana(int increment);
	UFUNCTION(BlueprintCallable)
	void DecreaseMana(int decrement);



};
