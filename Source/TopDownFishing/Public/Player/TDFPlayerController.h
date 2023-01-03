// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDFPlayerController.generated.h"

class ATDFPlayerCharacter;

UCLASS()
class TOPDOWNFISHING_API ATDFPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void OnMoveForward(const float Amount);
	void OnMoveRight(const float Amount);
	void OnUseToolPressed();
	void OnUseToolReleased();

private:

	UPROPERTY(VisibleAnywhere, Category = "Player")
	TObjectPtr<ATDFPlayerCharacter> PlayerCharacter;
};