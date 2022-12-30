// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDFPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ATDFBaseTool;

UCLASS()
class TOPDOWNFISHING_API ATDFPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ATDFPlayerCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "TDF Player")
	USpringArmComponent* GetPlayerSpringArm()
	{
		return SpringArmComponent;
	}

	UFUNCTION(BlueprintCallable, Category = "TDF Player")
	UCameraComponent* GetPlayerCamera()
	{
		return CameraComponent;
	}

private:

	UPROPERTY(EditAnywhere, Category = "Tools")
	TSubclassOf<ATDFBaseTool> ToolClass;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	void SpawnTool();
};