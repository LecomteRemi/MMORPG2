// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingCharacter.h"
#include <AIController.h>
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
AFightingCharacter::AFightingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentState = EBehaviorState::NONE;

}

// Called when the game starts or when spawned
void AFightingCharacter::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle updateTimer;
	GetWorld()->GetTimerManager().SetTimer(updateTimer, this, &AFightingCharacter::Update, 0.016f, true);
	
}

// Called every frame
void AFightingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFightingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFightingCharacter::SpawnAIController() {
	//this->SpawnD
}

void AFightingCharacter::MoveCommand(const FVector & location) {
	UE_LOG(LogTemp, Warning, TEXT("On se bouge"));
	targetLocation = location;
	currentState = EBehaviorState::MOVE;
}

void AFightingCharacter::AttackCommand(AFightingCharacter * enemy) {
	currentState = EBehaviorState::ATTACK;
	targetEnemy = enemy;
}
void AFightingCharacter::StopCommand() {
	currentState = EBehaviorState::NONE;
}
void AFightingCharacter::Update() {
	if (currentState == EBehaviorState::MOVE) {
		MoveToward(targetLocation);
	}
	else if (currentState == EBehaviorState::ATTACK) {
		if (targetEnemy == nullptr) {
			currentState = EBehaviorState::NONE;
		}
		if (FVector::Dist2D(this->GetActorLocation(), targetEnemy->GetActorLocation()) <= meleeRange) {
			GetMovementComponent()->StopActiveMovement();
			Attack(targetEnemy);
		}
		else {
			MoveToward((targetEnemy->GetActorLocation()));
		}
	}
}

void AFightingCharacter::MoveToward(const FVector& location) {
	AAIController* controller = Cast<AAIController>(GetController());
	if (controller) {
		controller->MoveToLocation(location);
	}
}
void AFightingCharacter::Attack(AFightingCharacter* enemy) {
	if (lastAttackTime + attackCoolDown <= GetWorld()->GetTimeSeconds()) {

		lastAttackTime = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("attack"));
	}

}


