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
#include "Item.h"
#include "LevelProgressionComponent.h"
// Sets default values
AFightingCharacter::AFightingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentState = EBehaviorState::NONE;

	stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats Component"));
	levelProgressionComponent = CreateDefaultSubobject<ULevelProgressionComponent>(TEXT("Level progression Component"));
	levelProgressionComponent->SetIsReplicated(true);
	levelProgressionComponent->stats = stats;
	levelProgressionComponent->character = this;

	
	

}

// Called when the game starts or when spawned
void AFightingCharacter::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle updateTimer;
	GetWorld()->GetTimerManager().SetTimer(updateTimer, this, &AFightingCharacter::Update, 0.016f, true);
	mana = stats->GetManaMax();
	PV = stats->GetPVMax();
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

	UE_LOG(LogTemp, Warning, TEXT("stooop"));
	currentState = EBehaviorState::NONE;
}
void AFightingCharacter::Update() {
	RegenPVAndMana();
	UpdateCooldown();
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
			if(targetInteraction->IsInteractable())
			targetInteraction->Interact(this);

			UE_LOG(LogTemp, Warning, TEXT("On interagit"));
			currentState = EBehaviorState::NONE;
			GetMovementComponent()->StopActiveMovement();
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
	if (usedAbilityClass == nullptr || usedAbility == nullptr) return;
	if (abilityList[usedAbilityClass] > 0) return;
	if (currentAbilityState == EAbilityState::GET_IN_RANGE) {
		if (spellTargetType == ETargetType::FIGHTER && FVector::Dist2D(this->GetActorLocation(), spellTarget.fightingCharacter->GetActorLocation()) > usedAbility->skillAbilityDetails->range) {
			MoveToward(spellTarget.fightingCharacter->GetActorLocation());
		}
		else if (spellTargetType == ETargetType::LOCATION && FVector::Dist2D(this->GetActorLocation(), (spellTarget.location)) > usedAbility->skillAbilityDetails->range) {

			MoveToward((spellTarget.location));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Je me prepare a lancer le sort"));
			currentAbilityState = EAbilityState::START_CASTING;
			GetMovementComponent()->StopActiveMovement();
			startCastingTime = GetWorld()->TimeSeconds;
		}
	}
	if (currentAbilityState == EAbilityState::START_CASTING){
		if (GetWorld()->TimeSeconds >= startCastingTime + usedAbility->skillAbilityDetails->preparationTime) {

			UE_LOG(LogTemp, Warning, TEXT("Je lance le sort %d"), (int) HasAuthority());
			currentAbilityState = EAbilityState::CAST;
			//ASkillAbility* abilityInstance = GetWorld()->SpawnActor<ASkillAbility>(mockupAbilityClass);
			usedAbility->SetActorLocation(this->GetActorLocation());
			mana -= usedAbility->skillAbilityDetails->manaCost;
			usedAbility->ActivateAbility(this);
		}
	}
	if (currentAbilityState == EAbilityState::CAST) {

		//currentAbilityState = EAbilityState::END_CASTING;
	}
	if (currentAbilityState == EAbilityState::END_CASTING && GetWorld()->TimeSeconds >= endCastingTime + usedAbility->skillAbilityDetails->delayTime) {
		currentState = EBehaviorState::NONE;
		currentAbilityState = EAbilityState::NONE;
		//abilityList[usedAbilityClass] = usedAbilityClass.GetDefaultObject()->skillAbilityDetails->cooldown;
		SetCooldownOnClient(usedAbilityClass);
		usedAbilityClass = nullptr;
		if (HasAuthority()) {
			usedAbility->Destroy();
		}
		usedAbility = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Je peux bouger"));
	}
}


void AFightingCharacter::EndCasting() {
	currentAbilityState = EAbilityState::END_CASTING;
	
	UE_LOG(LogTemp, Warning, TEXT("Le sort est lancee"));
	this->endCastingTime = GetWorld()->TimeSeconds;
}

void AFightingCharacter::UseItem(TSubclassOf<AItem> itemClass) {

	if (GetNbItem(itemClass) > 0) {
		AItem* item = GetWorld()->SpawnActor<AItem>(itemClass);
		item->ActivateItem(this);
		item->Destroy();
		DecreaseNbItem(itemClass, 1);
		UE_LOG(LogTemp, Warning, TEXT("item numero"));
	}
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
			enemy->TakeHit(damages,this);
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
void AFightingCharacter::TakeHit(int damage, AFightingCharacter * attacker) {
	PV -= damage;
	PV = PV < 0 ? 0 : PV;
	if (PV < 1) {
		attacker->levelProgressionComponent->AddExp(10);
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
	UE_LOG(LogTemp, Warning, TEXT("-------------------"));
	usedAbility = GetWorld()->SpawnActor<ASkillAbility>(usedAbilityClass);
	usedAbility->SetActorLabel("Squalala");
	UE_LOG(LogTemp, Warning, TEXT("Je lance un sort sur ce type"));

	spellTarget.fightingCharacter = target;
	spellTargetType = ETargetType::FIGHTER;
	currentState = EBehaviorState::CAST;
	currentAbilityState = EAbilityState::GET_IN_RANGE;

}
void AFightingCharacter::CastCommand(TSubclassOf<ASkillAbility> abilityClass, FVector target) {
	if (!CanInterruptAction()) return;
	usedAbilityClass = abilityClass;
	UE_LOG(LogTemp, Warning, TEXT("-------------------"));
	usedAbility = GetWorld()->SpawnActor<ASkillAbility>(usedAbilityClass);
	UE_LOG(LogTemp, Warning, TEXT("Je lance un sort a un endroit"));
	usedAbility->SetActorLabel("Squalala");

	spellTarget.location = target;
	spellTargetType = ETargetType::LOCATION;
	currentState = EBehaviorState::CAST;
	currentAbilityState = EAbilityState::GET_IN_RANGE;
}
void AFightingCharacter::CastCommand(TSubclassOf<ASkillAbility> abilityClass) {
	if (!CanInterruptAction()) return;
	usedAbilityClass = abilityClass;
	UE_LOG(LogTemp, Warning, TEXT("-------------------"));
	usedAbility = GetWorld()->SpawnActor<ASkillAbility>(usedAbilityClass);
	usedAbility->SetActorLabel("Squalala");

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
	DOREPLIFETIME(AFightingCharacter, PV);
	DOREPLIFETIME(AFightingCharacter, stats);
}

void AFightingCharacter::AddAbility_Implementation(TSubclassOf<ASkillAbility> ability) {
	abilityList.Add(ability,0);
	//SetCooldownOnClient(ability);
	UE_LOG(LogTemp, Warning, TEXT("Todokeyo!"));
}


void AFightingCharacter::UpdateCooldown() {
	float deltaTime = GetWorld()->GetDeltaSeconds();
	for (auto& elem : abilityList)
	{
		float value = 0;
		if (elem.Value > 0) {
			value = elem.Value - deltaTime;
			value = value < 0 ? 0 : value;
			abilityList[elem.Key] = value;
			//UE_LOG(LogTemp, Warning, TEXT("Cooldown %f"), abilityList[elem.Key]);
		}
	}
}

void AFightingCharacter::SetCooldownOnClient_Implementation(TSubclassOf<ASkillAbility> ability) {
	//if (HasAuthority()) return;
	if (!abilityList.Contains(ability)) {
		abilityList.Add(ability,ability.GetDefaultObject()->skillAbilityDetails->cooldown);
	}
	else {
		abilityList[ability] = ability.GetDefaultObject()->skillAbilityDetails->cooldown;
	}
}


int AFightingCharacter::GetNbItem(TSubclassOf<AItem> item) {
	if (itemList.Contains(item)) {
		return itemList[item];
	}
	return 0;
}
void AFightingCharacter::IncreaseNbItem_Implementation(TSubclassOf<AItem> item, int increment) {
	if (itemList.Contains(item)) {
		itemList[item] = itemList[item] + increment;
	}
	else {
		itemList.Add(item, increment);
	}
}
void AFightingCharacter::DecreaseNbItem_Implementation(TSubclassOf<AItem> item, int decrement) {
	if (itemList.Contains(item)) {
		int value = itemList[item] - decrement;
		itemList[item] = value > 0 ? value : 0;
	}
}

void AFightingCharacter::IncreasePV(int increment) {
	PV = PV + increment > stats->GetPVMax() ? stats->GetPVMax() : PV + increment;
}
void AFightingCharacter::DecreasePV(int decrement) {
	PV = PV < decrement ? 0 : PV - decrement;
}
void AFightingCharacter::IncreaseMana(int increment) {
	mana = mana+ increment > stats->GetManaMax() ? stats->GetManaMax() : mana + increment;
}
void AFightingCharacter::DecreaseMana(int decrement) {
	mana = mana < decrement ? 0 : mana - decrement;
}