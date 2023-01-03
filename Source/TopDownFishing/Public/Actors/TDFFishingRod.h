// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "Actors/TDFBaseTool.h"
#include "TDFFishingRod.generated.h"

class UWidgetComponent;
class ATDFPlayerCharacter;
class UTDFFishPondComponent;
class UTDFFishAnnounceWidget;

UENUM()
enum class EFishingRodState
{
	NotUsed,
	Casting,
	Waiting,
	Pulling
};

UCLASS()
class TOPDOWNFISHING_API ATDFFishingRod : public ATDFBaseTool
{
	GENERATED_BODY()

public:

	ATDFFishingRod();

	virtual void BeginPlay() override;
	virtual void BeginAction() override;
	virtual void EndAction() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fishing Rod")
	float MaxCastDistance = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fishing Rod")
	float CastingSpeed = 70.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fishing Rod")
	float CurrentCastOffset = 0.0f;

protected:

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Fishing Rod")
	bool GetFishingLocation(FHitResult& Result);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fishing Rod")
	TSubclassOf<AActor> FishingCastClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fishing Rod")
	TEnumAsByte<ECollisionChannel> FishingChannel;

	UPROPERTY(VisibleAnywhere, Category = "Fishing Rod")
	EFishingRodState RodState = EFishingRodState::NotUsed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fishing Rod")
	TSubclassOf<UTDFFishAnnounceWidget> FishAnnounceWidgetClass;

private:

	void ThrowCast(const FVector Location);
	void StartPlayerMontage(const FName MontageName, const float Rate = 1.0f);
	void StopPlayerMontage();
	void OnFishBite();
	void OnFinish();

	TObjectPtr<ATDFPlayerCharacter> PlayerOwner;
	TObjectPtr<AActor> FishingCast;
	TObjectPtr<UTDFFishPondComponent> CurrentPond;
	TObjectPtr<UTDFFishAnnounceWidget> FishAnnounceWidget;

	bool bCastBackward = false;
	bool bCaughtFish = false;
};