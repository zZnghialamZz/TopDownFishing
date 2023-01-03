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

	void SpawnTool();

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveForward(const float Amount);
	void MoveRight(const float Amount);
	void StartUseCurrentTool();
	void StopUseCurrentTool();

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

	UFUNCTION(BlueprintCallable, Category = "TDF Player")
	ATDFBaseTool* GetCurrentTool()
	{
		return CurrentTool;
	}

	UFUNCTION(BlueprintCallable, Category = "TDF Player")
	bool IsFishing() const;

private:

	UPROPERTY(EditAnywhere, Category = "Tools")
	TSubclassOf<ATDFBaseTool> ToolClass;

	UPROPERTY(VisibleAnywhere, Category = "Tool")
	TObjectPtr<ATDFBaseTool> CurrentTool;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
};