// Fill out your copyright notice in the Description page of Project Settings.


#include "Loot.h"

void ALoot::Interact(AFightingCharacter* interactor) {

	UE_LOG(LogTemp, Warning, TEXT("Hatsune Miku"));
	DestroyOnServer();

}
void ALoot::DestroyOnServer_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("Kasane Teto %d"), HasAuthority());
	this->Destroy();
}
void ALoot::DestroyOnClient_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("Neru %d"), HasAuthority());
	this->Destroy();
}
void ALoot::SetQuantity(int quantity_) {
	this->quantity = quantity_;
}