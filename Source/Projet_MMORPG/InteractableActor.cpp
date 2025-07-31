// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bNetLoadOnClient = false;
	bReplicates = true;

}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
bool AInteractableActor::IsInteractable() {
	return true;
}
void AInteractableActor::Interact(AFightingCharacter* character) {
	UE_LOG(LogTemp, Warning, TEXT("Interaction"));
}
