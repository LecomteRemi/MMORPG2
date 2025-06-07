// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingCharacter.h"
#include <AIController.h>
#include "InteractableActor.h"
#include "StatsComponent.h"
#include "SkillAbility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "SkillAbilityDetails.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AFightingCharacter::AFightingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentState = EBehaviorState::NONE;

	stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	mana = 0;
	
	

}

// Called when the game starts or when spawned
void AFightingCharacter::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle updateTimer;
	GetWorld()->GetTimerManager().SetTimer(updateTimer, this, &AFightingCharacter::Update, 0.016f, true);

	GetCharacterMovement()->MaxWalkSpeed = attributes->walkSpeed;
	
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
	if (!CanInterruptAction()) return;
	UE_LOG(LogTemp, Warning, TEXT("On se bouge"));
	targetLocation = location;
	currentState = EBehaviorState::MOVE;
}

void AFightingCharacter::AttackCommand(AFightingCharacter * enemy) {
	if (!CanInterruptAction()) return;
	currentState = EBehaviorState::ATTACK;
	targetEnemy = enemy;
}

void AFightingCharacter::InteractCommand(AInteractableActor* interactable) {
	if (!CanInterruptAction()) return;
	currentState = EBehaviorState::INTERACT;
	targetInteraction = interactable;
}
void AFightingCharacter::StopCommand() {
	if (!CanInterruptAction()) return;
	currentState = EBehaviorState::NONE;
}
void AFightingCharacter::Update() {
	RegenPVAndMana();
	if (currentState == EBehaviorState::MOVE) {
		MoveToward(targetLocation);
	}
	else if (currentState == EBehaviorState::ATTACK) {
		if (targetEnemy == nullptr) {
			currentState = EBehaviorState::NONE;
		}
		else {
			if (FVector::Dist2D(this->GetActorLocation(), targetEnemy->GetActorLocation()) <= attributes->meleeRange) {
				GetMovementComponent()->StopActiveMovement();
				Attack(targetEnemy);
			}
			else {
				MoveToward((targetEnemy->GetActorLocation()));
			}
		}
	}
	else if (currentState == EBehaviorState::INTERACT) {
		if (targetInteraction == nullptr) {
			currentState = EBehaviorState::NONE;
		}
		else if(FVector::Dist2D(this->GetActorLocation(),targetInteraction->GetActorLocation()) <= attributes->interactionRange) {
			targetInteraction->Interact(this);

			UE_LOG(LogTemp, Warning, TEXT("On interagit"));
			currentState = EBehaviorState::NONE;
		}
		else {
			MoveToward(targetInteraction->GetActorLocation());
		}
	}
	else if (currentState == EBehaviorState::CAST) {
		UpdateAbility();
	}
}


void AFightingCharacter::UpdateAbility() {
	float castDistance = 200;
	float castPreparationTime = 2;
	float castDelayTime=1;
	if (usedAbilityClass == nullptr) return;
	if (currentAbilityState == EAbilityState::GET_IN_RANGE) {
		if (spellTargetType == ETargetType::FIGHTER && FVector::Dist2D(this->GetActorLocation(), spellTarget.fightingCharacter->GetActorLocation()) > castDistance) {
			MoveToward(spellTarget.fightingCharacter->GetActorLocation());
		}
		else if (spellTargetType == ETargetType::LOCATION && FVector::Dist2D(this->GetActorLocation(), (spellTarget.location)) > castDistance) {

			MoveToward((spellTarget.location));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Je me prepare a lancer le sort"));
			currentAbilityState = EAbilityState::START_CASTING;
			GetMovementComponent()->StopActiveMovement();
			startCastingTime = GetWorld()->TimeSeconds;
		}
	}
	else if (currentAbilityState == EAbilityState::START_CASTING){
		if (GetWorld()->TimeSeconds >= startCastingTime + castPreparationTime) {

			UE_LOG(LogTemp, Warning, TEXT("Je lance le sort %d"), (int) HasAuthority());
			currentAbilityState = EAbilityState::CAST;
			ASkillAbility* abilityInstance = GetWorld()->SpawnActor<ASkillAbility>(mockupAbilityClass);
			mana -= abilityInstance->skillAbilityDetails->manaCost;
			abilityInstance->ActivateAbility(this);
		}
	}
	else if (currentAbilityState == EAbilityState::CAST) {

		//currentAbilityState = EAbilityState::END_CASTING;
	}
	else if (currentAbilityState == EAbilityState::END_CASTING && GetWorld()->TimeSeconds >= endCastingTime + castDelayTime) {
		currentState = EBehaviorState::NONE;
		currentAbilityState = EAbilityState::NONE;
		usedAbilityClass = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Je peux bouger"));
	}
}


void AFightingCharacter::EndCasting() {
	currentAbilityState = EAbilityState::END_CASTING;

	UE_LOG(LogTemp, Warning, TEXT("Le sort est lancee"));
	this->endCastingTime = GetWorld()->TimeSeconds;
}

void AFightingCharacter::MoveToward(const FVector& location) {
	AAIController* controller = Cast<AAIController>(GetController());
	if (controller) {
		controller->MoveToLocation(location);
	}
}
void AFightingCharacter::Attack(AFightingCharacter* enemy) {
	if (lastAttackTime + stats->GetAttackSpeed() <= GetWorld()->GetTimeSeconds()) {

		lastAttackTime = GetWorld()->GetTimeSeconds();

		float precisionRoll = FMath::FRand() * FMath::FRand();
		if (precisionRoll < stats->GetPrecision() - enemy->stats->GetAvoidance()) {
			int damages = stats->GetDamages() - enemy->stats->GetArmor();
			enemy->TakeHit(damages);
			UE_LOG(LogTemp, Warning, TEXT("J'attaque precision: %f, esquive: %f"), stats->GetPrecision(), enemy->stats->GetAvoidance());
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Rate precision: %f, esquive: %f"), stats->GetPrecision(), enemy->stats->GetAvoidance());
		}


	}
	
}

void AFightingCharacter::SetAttributes(UFightingCharacterAttributes* fightingCharacterAttributes) {
	this->attributes = attributes;
	GetCharacterMovement()->MaxWalkSpeed = fightingCharacterAttributes->walkSpeed;

}

void AFightingCharacter::RegenPVAndMana() {
	PV += stats->GetRegenPV() * GetWorld()->GetDeltaSeconds();
	PV = PV < 0 ? 0 : PV > stats->GetPVMax() ? stats->GetPVMax() : PV;
	
	mana += stats->GetRegenMana() * GetWorld()->GetDeltaSeconds();
	mana = mana < 0 ? 0 : mana > stats->GetManaMax() ? stats->GetManaMax() : mana;
	//mana = 0;
}
void AFightingCharacter::TakeHit(int damage) {
	PV -= damage;
	PV = PV < 0 ? 0 : PV;
	if (PV < 1) {
		Die();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PV: %f"), PV);
	}
}
void AFightingCharacter::Die() {
	TSubclassOf<AActor> classToFind = AFightingCharacter::StaticClass();
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, foundActors);

	for (int i = 0; i < foundActors.Num();i++) {
		Cast<AFightingCharacter>(foundActors[i])->SignalDeathOf(this);
	}
	UE_LOG(LogTemp, Warning, TEXT("Toujours vivant"));
	this->Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Je suis mort"));
	
}
void AFightingCharacter::SignalDeathOf(AFightingCharacter* deadFighter) {
	if (targetEnemy == deadFighter) {
		StopCommand();
		UE_LOG(LogTemp, Warning, TEXT("Exp: %d"), FMath::FloorToInt(deadFighter->stats->GetLevel() * deadFighter->stats->statsGrowth->expCoeff));
	}
}

UStatsComponent * AFightingCharacter::GetStats() {
	return stats;
}
void AFightingCharacter::CastCommand(TSubclassOf<ASkillAbility> abilityClass, AFightingCharacter* target) {
	if (!CanInterruptAction()) return;

	usedAbilityClass = abilityClass;
	UE_LOG(LogTemp, Warning, TEXT("Je lance un sort sur ce type"));

	spellTarget.fightingCharacter = target;
	spellTargetType = ETargetType::FIGHTER;
	currentState = EBehaviorState::CAST;
	currentAbilityState = EAbilityState::GET_IN_RANGE;

}
void AFightingCharacter::CastCommand(TSubclassOf<ASkillAbility> abilityClass, FVector target) {
	if (!CanInterruptAction()) return;
	usedAbilityClass = abilityClass;
	UE_LOG(LogTemp, Warning, TEXT("Je lance un sort a un endroit"));

	spellTarget.location = target;
	spellTargetType = ETargetType::LOCATION;
	currentState = EBehaviorState::CAST;
	currentAbilityState = EAbilityState::GET_IN_RANGE;
}
void AFightingCharacter::CastCommand(TSubclassOf<ASkillAbility> abilityClass) {
	if (!CanInterruptAction()) return;
	usedAbilityClass = abilityClass;
	UE_LOG(LogTemp, Warning, TEXT("Je lance un sort"));

	spellTargetType = ETargetType::NONE;
	currentState = EBehaviorState::CAST;
	currentAbilityState = EAbilityState::GET_IN_RANGE;
}
bool AFightingCharacter::CanInterruptAction() {
	return currentState != EBehaviorState::CAST || (TArray<EAbilityState>({ EAbilityState::NONE, EAbilityState::GET_IN_RANGE })).Contains(currentAbilityState);
}
void AFightingCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFightingCharacter, mana);
}