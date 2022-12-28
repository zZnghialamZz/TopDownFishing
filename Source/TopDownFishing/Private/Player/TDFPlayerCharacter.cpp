// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/TDFPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATDFPlayerCharacter::ATDFPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(ACharacter::GetMovementComponent());
	if (MovementComponent)
	{
		bUseControllerRotationYaw = false;
		
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->bConstrainToPlane = true;
		MovementComponent->bSnapToPlaneAtStart = true;
		MovementComponent->bUseControllerDesiredRotation = false;
	}
}

// Called when the game starts or when spawned
void ATDFPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATDFPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATDFPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATDFPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATDFPlayerCharacter::MoveRight);
}

void ATDFPlayerCharacter::MoveForward(const float Amount)
{
	AddMovementInput(CameraComponent->GetForwardVector(), Amount);
}

void ATDFPlayerCharacter::MoveRight(const float Amount)
{
	AddMovementInput(CameraComponent->GetRightVector(), Amount);
}