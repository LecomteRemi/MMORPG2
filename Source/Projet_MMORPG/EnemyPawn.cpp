// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "AbilityList.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		Init();
		initiated = true;
	}
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!initiated && fightingCharacter != nullptr) {
		initiated = true;

		if (abilityList != nullptr) {
			for (int i = 0; i < abilityList->abilities.Num() - 1; i++) {
				fightingCharacter->AddAbility(abilityList->abilities[i]);
			}
		}
	}

	if (fightingCharacter == nullptr) {
		this->fightingCharacter = Cast<AFightingCharacter>(GetAttachParentActor());
	}
}

void AEnemyPawn::MoveToward_Implementation(FVector location) {
	fightingCharacter->MoveCommand(location);
	fightingCharacter->AddAbility(abilityList->abilities[2]);

}
void AEnemyPawn::Attack_Implementation(AFightingCharacter* enemy) {
	if (enemy != fightingCharacter && enemy != nullptr)
		fightingCharacter->AttackCommand(enemy);
}
void AEnemyPawn::StopAction_Implementation() {

}
void AEnemyPawn::Init() {

	fightingCharacter = GetWorld()->SpawnActor<AFightingCharacter>(fightingCharacterClass, GetActorLocation(), GetActorRotation());
	AttachToActor(fightingCharacter, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorRelativeLocation(FVector::ZeroVector);
	fightingCharacter->SpawnDefaultController();
	fightingCharacter->SetAttributes(attributes);
	if (abilityList != nullptr) {
		if (fightingCharacter != nullptr) {
			for (int i = 0; i < abilityList->abilities.Num() - 1; i++) {
				fightingCharacter->AddAbility(abilityList->abilities[i]);
			}
		}
	}


}
void AEnemyPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyPawn, fightingCharacter);
}
void AEnemyPawn::Interact_Implementation(AInteractableActor* interactable) {
	fightingCharacter->InteractCommand(interactable);
}

void AEnemyPawn::UseAction_Implementation(TSubclassOf<ASkillAbility> skillAbilityClass) {
	fightingCharacter->CastCommand(skillAbilityClass);

}
void AEnemyPawn::UseActionFighter_Implementation(TSubclassOf<ASkillAbility> skillAbilityClass, AFightingCharacter* target) {
	fightingCharacter->CastCommand(skillAbilityClass, target);
}
void AEnemyPawn::UseActionLocation_Implementation(TSubclassOf<ASkillAbility> skillAbilityClass, const  FVector& target) {
	fightingCharacter->CastCommand(skillAbilityClass, target);
}
void AEnemyPawn::AddAbility(TSubclassOf<ASkillAbility> ability) {
	fightingCharacter->AddAbility(ability);

}
