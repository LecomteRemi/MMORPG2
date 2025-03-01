// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EBehaviorState.h"
#include "FightingCharacter.generated.h"



UCLASS()
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

	UPROPERTY()
	FVector targetLocation;
	AFightingCharacter* targetEnemy;


	UPROPERTY(EditAnywhere)
	float meleeRange;

	UFUNCTION()
	void MoveToward(const FVector& location);
	void Attack(AFightingCharacter * enemy);

	double lastAttackTime;

	UPROPERTY(EditAnywhere)
	double attackCoolDown;
	//targetInteractableObject

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SpawnAIController();

	void MoveCommand(const FVector & location);
	void AttackCommand(AFightingCharacter* enemy);
	void StopCommand();
	void Update();


};
