// MIT License - Copyright (c) 2022 Nghia Lam

#include "Player/TDFPlayerController.h"

#include "Camera/CameraComponent.h"
#include "Player/TDFPlayerCharacter.h"

ATDFPlayerController::ATDFPlayerController() {}

void ATDFPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	PlayerCharacter = Cast<ATDFPlayerCharacter>(GetPawn());
}

void ATDFPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATDFPlayerController::OnMoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATDFPlayerController::OnMoveRight);
}

void ATDFPlayerController::OnMoveForward(const float Amount)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetPlayerCamera()->GetForwardVector(), Amount);
	}
}

void ATDFPlayerController::OnMoveRight(const float Amount)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetPlayerCamera()->GetRightVector(), Amount);
	}
}