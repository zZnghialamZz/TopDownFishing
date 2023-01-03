// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDFFishPondComponent.generated.h"

class ATDFFish;
class UBoxComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOPDOWNFISHING_API UTDFFishPondComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UTDFFishPondComponent();

	DECLARE_EVENT(UTDFFishPondComponent, FTDFFishBiteEvent)
	FTDFFishBiteEvent& GetFishBiteEvent()
	{
		return FishBiteEvent;
	}

	UFUNCTION(BlueprintCallable)
	void SetCastLocation(const FVector& Location)
	{
		CastLocation = Location;
	}

	UFUNCTION(BlueprintCallable)
	bool SpawnFish();

	UFUNCTION(BlueprintCallable)
	void DestroyFish();

	UPROPERTY(VisibleAnywhere, Category = "Fish Pond")
	TObjectPtr<ATDFFish> CurrentFish;

protected:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Pond")
	TArray<TSubclassOf<ATDFFish>> FishList;

	UPROPERTY(VisibleAnywhere, Category = "Fish Pond")
	UBoxComponent* SpawnBox;

private:

	bool IsFishWithinReach() const;

	FVector CastLocation;
	FTDFFishBiteEvent FishBiteEvent;
};