// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDFFish.generated.h"

class UStaticMeshComponent;

UCLASS()
class TOPDOWNFISHING_API ATDFFish : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	ATDFFish();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fish")
	FString FishName = "DefaultFish";

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fish")
	TObjectPtr<UStaticMeshComponent> FishMesh;
};