// MIT License - Copyright (c) 2022 Nghia Lam

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDFBaseTool.generated.h"

class UStaticMeshComponent;

UCLASS()
class TOPDOWNFISHING_API ATDFBaseTool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATDFBaseTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tool")
	TObjectPtr<UStaticMeshComponent> ToolMesh;
};
