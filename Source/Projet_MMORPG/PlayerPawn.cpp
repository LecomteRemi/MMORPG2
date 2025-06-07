// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {
		Init();

		
	}
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if ( fightingCharacter == nullptr) {
		this->fightingCharacter = Cast<AFightingCharacter>(GetAttachParentActor());
		if(fightingCharacter != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Fighitng Character OK!!!"));
	}

	
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::MoveToward_Implementation(FVector location) {
	UE_LOG(LogTemp, Warning, TEXT("On y va"));
	fightingCharacter->MoveCommand(location);
}
void APlayerPawn::Attack_Implementation(AFightingCharacter * enemy) {
	if (enemy != fightingCharacter && enemy != nullptr)
		fightingCharacter->AttackCommand(enemy);
}
void APlayerPawn::StopAction_Implementation() {
	
}
void APlayerPawn::Init_Implementation() {
	UE_LOG(LogTemp, Warning, TEXT("Init"));
	
	fightingCharacter = GetWorld()->SpawnActor<AFightingCharacter>(fightingCharacterClass, GetActorLocation(), GetActorRotation());
	AttachToActor(fightingCharacter, FAttachmentTransformRules::KeepRelativeTransform);
	SetActorRelativeLocation(FVector::ZeroVector);
	fightingCharacter->SpawnDefaultController();
	fightingCharacter->SetAttributes(attributes);
	
}
void APlayerPawn::Interact_Implementation(AInteractableActor* interactable) {
	fightingCharacter->InteractCommand(interactable);
}

void APlayerPawn::UseAction_Implementation( TSubclassOf<ASkillAbility> skillAbilityClass) {
	fightingCharacter->CastCommand(skillAbilityClass);
}
void APlayerPawn::UseActionFighter_Implementation(TSubclassOf<ASkillAbility> skillAbilityClass, AFightingCharacter * target) {
	fightingCharacter->CastCommand(skillAbilityClass, target);
}
void APlayerPawn::UseActionLocation_Implementation(TSubclassOf<ASkillAbility> skillAbilityClass, const  FVector& target) {
	fightingCharacter->CastCommand(skillAbilityClass, target);
}


