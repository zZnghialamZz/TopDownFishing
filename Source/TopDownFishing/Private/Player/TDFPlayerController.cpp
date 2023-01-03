// MIT License - Copyright (c) 2022 Nghia Lam

#include "Player/TDFPlayerController.h"

#include "Player/TDFPlayerCharacter.h"

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
	InputComponent->BindAction("UseTool", IE_Pressed, this, &ATDFPlayerController::OnUseToolPressed);
	InputComponent->BindAction("UseTool", IE_Released, this, &ATDFPlayerController::OnUseToolReleased);
}

void ATDFPlayerController::OnMoveForward(const float Amount)
{
	if (PlayerCharacter) PlayerCharacter->MoveForward(Amount);
}

void ATDFPlayerController::OnMoveRight(const float Amount)
{
	if (PlayerCharacter) PlayerCharacter->MoveRight(Amount);
}

void ATDFPlayerController::OnUseToolPressed()
{
	if (PlayerCharacter) PlayerCharacter->StartUseCurrentTool();
}

void ATDFPlayerController::OnUseToolReleased()
{
	if (PlayerCharacter) PlayerCharacter->StopUseCurrentTool();
}